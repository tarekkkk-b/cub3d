/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/18 13:48:54 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_file(char *path, t_file *file)
{
	char	*line;

	file->file_size = 1;
	file->file = NULL;
	if (ft_strncmp(&path[ft_strlen(path) - 4], ".cub", 4) != 0)
		(write(2, USAGE, ft_strlen(USAGE)), exit(1));
	file->fd = open(path, O_RDONLY);
	if (file->fd == -1)
		(write(2, FILE_404, ft_strlen(FILE_404)), exit(1));
	line = get_next_line(file->fd);
	if (!line)
		(write(2, EMPTY, ft_strlen(EMPTY)), exit(1));
	while (line)
	{
		file->file_size++;
		free(line);
		line = get_next_line(file->fd);
	}
	free(line);
	if (file->file_size < 9)
		(write(2, INVALID, ft_strlen(INVALID)), exit(1));
	close (file->fd);
	file->fd = -1;
}

void	get_file(char *path, t_file *file)
{
	int	i;

	i = -1;
	file->fd = open(path, O_RDONLY);
	file->file = malloc(sizeof(char *) * file->file_size);
	if (!file->file)
		(write(2, INVALID, ft_strlen(INVALID)), exit(1));
	while (++i < file->file_size - 1)
		file->file[i] = ft_strtrim(get_next_line(file->fd), "\n");
	file->file[i++] = NULL;
	close(file->fd);
	file->fd = -1;
}

int	empty_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
}

int	collected_textures(t_textures *textures)
{
	if (textures->east
		&& textures->west
		&& textures->south
		&& textures->north
		&& textures->floor != -1
		&& textures->ceiling != -1)
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
}

void	init_textures(t_textures *textures)
{
	textures->east = NULL;
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->ceiling_txtr = NULL;
	textures->floor_txtr = NULL;
	textures->ceiling = -1;
	textures->floor = -1;
}

int	assign_texture(char *str, void **texture, t_game *game, int err_flag)
{
	char	**holder;
	int		height;
	int		width;
	int		fd;

	holder = ft_split(str, ' ');
	if (!holder[0] || !holder[1] || holder[2])
	{
		if (err_flag)
			write(2, INV_TXTR, ft_strlen(INV_TXTR));
		return(0);
	}
	fd = open(holder[1], O_RDONLY);
	if (fd == -1)
	{
		if (err_flag)
			write(2, TXTR_404, ft_strlen(TXTR_404));
		return(0);
	}
	close(fd);
	(*texture) = mlx_xpm_file_to_image(game->mlx, holder[1], &width, &height);
	if (!(*texture))
	{
		if (err_flag)
			write(2, XPM, ft_strlen(XPM));
		return(0);
	}
	free_array(holder);
	return (1);
}

int	create_rgb(int *color_arr)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color_arr[0];
	g = color_arr[1];
	b = color_arr[2];
	a = 0x00000000;
	return (r << 16 | g << 8 | b | a);
}

int	set_colour(int i, int *arr, int clr_counter, char *str)
{
	int		index;
	char	colour[4];

	index = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (index > 2)
			return (-1);
		colour[index++] = str[i++];
	}
	colour[index] = '\0';
	arr[clr_counter] = ft_atoi(colour);
	if (arr[clr_counter] > 255 || arr[clr_counter] < 0)
		return (-1);
	i--;
	return (i);
}

void	assign_colour(char *str, int *colour, int *arr, t_game *game)
{
	int		i;
	int		clr_counter;
	int		comma_counter;
	int		letter_counter;
	char	**temp;
	
	
	i = 0;
	temp = ft_split(str, ' ');
	if (temp[0] && temp[1] && !temp[2])
	{
		if (temp[0][0] == 'C')
		{
			if (assign_texture(str, &game->textures.ceiling_txtr, game->mlx, 0))
			{
				game->textures.ceiling = 0;
				return (free_array(temp));
			}
		}
		else if (temp[0][0] == 'F')
		{
			if (assign_texture(str, &game->textures.floor_txtr, game->mlx, 0))
			{
				game->textures.floor = 0;
				return (free_array(temp));
			}
		}
	}
	free_array(temp);
	clr_counter = 0;
	comma_counter = 0;
	letter_counter = 0;
	while (str[i] && (str[i] == ' ' || str[i] == 'F' || str[i] == 'C'))
	{
		if (str[i] == 'C' || str[i] == 'F')
		{
			if (!letter_counter)
				letter_counter = 1;
			else
				(printf("%c: not for the colour\n", str[i]), exit(1));
		}
		i++;
	}
	while (str[i])
	{
		if (str[i] && str[i] != ',' && str[i] != ' ' && !ft_isdigit(str[i]))
			(printf("%c: not for the colour\n", str[i]), exit(1));
		if (str[i] == ',')
			comma_counter++;
		if (ft_isdigit(str[i]))
		{
			i = set_colour(i, arr, clr_counter, str);
			clr_counter++;
			if (comma_counter != clr_counter - 1)
				(printf("wrong count\n"), exit(1));
		}
		if (i == -1)
			(printf("colour problem\n"), exit(1));
		if (clr_counter > 3)
			(printf("wrong count\n"), exit(1));
		i++;
	}
	if (clr_counter != 3 || comma_counter != 2)
		(printf("colour problem\n"), exit(1));
	(*colour) = create_rgb(arr);
}

int	check_texture(char *str, t_textures *textures, t_game *game)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == NORTH && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, &textures->north, game, 1);
	else if (str[i] == SOUTH && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, &textures->south, game, 1);
	else if (str[i] == WEST && str[i + 1] == 'E' && str[i + 2] == ' ')
		assign_texture(str, &textures->west, game, 1);
	else if (str[i] == EAST && str[i + 1] == 'A' && str[i + 2] == ' ')
		assign_texture(str, &textures->east, game, 1);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		assign_colour(str, &textures->ceiling, textures->c_arr, game);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		assign_colour(str, &textures->floor, textures->f_arr, game);
	else
		return (0);
	return (1);
}

int	get_textures(t_file *file, t_textures *textures, t_game *game)
{
	int	i;

	i = -1;
	init_textures(textures);
	while (file->file[++i])
	{
		if (collected_textures(textures))
			break ;
		if (!empty_line(file->file[i]))
			if (!check_texture(file->file[i], textures, game))
			{
				printf("n: %s\ne: %s\nw: %s\ns: %s\nc: %d\nf: %d\n", textures->north, textures->east, textures->west, textures->south, textures->ceiling, textures->floor);
				(printf("%s: not a texture\n", file->file[i]), exit (1));
			}
	}
	while (file->file[i] && empty_line(file->file[i]))
		i++;
	printf("ceiling: %x\n", textures->ceiling);
	printf("floor: %x\n", textures->floor);
	return (i);
}

int	map_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr("10NEWSD ", str[i]))
			(printf("BAD ELEMENT\n"), exit(1));
	return (1);
}

int	check_len(int index, t_map *map, t_file *file)
{
	int	empty;
	int	width;

	empty = 0;
	width = 0;
	map->height = 0;
	while (file->file[index] && empty_line(file->file[index]))
		index++;
	map->width = ft_strlen(file->file[index]);
	while (file->file[index] && map_line(file->file[index]))
	{
		width  = ft_strlen(file->file[index]);
		if (width > map->width)
			map->width = width;
		// printf("line:	<<%s>>	length:	%zu\n", file->file[index], ft_strlen(file->file[index]));
		if (empty_line(file->file[index]))
		{
			empty = 1;
			break ;
		}
		index++;
		map->height++;
	}
	while (file->file[index])
	{
		if (!empty_line(file->file[index]) && empty)
			return (-1);
		index++;
	}
	// printf("map width: %d\n", map->width);
	return (map->height);
}

void	get_map(t_file *file, t_map *map, int index)
{
	map->height = check_len(index, map, file);
	if (map->height == -1 || map->height < 3)
		(printf("womp womp map problem\n"), exit(1));
	map->map = malloc(sizeof(char *) * (map->height + 1));
	while (file->file[index] && empty_line(file->file[index]))
		index++;
	int i = 0;
	printf("map height: %d\n", map->height);
	printf("map width: %d\n", map->width);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		ft_strlcpy(map->map[i], file->file[index], map->width + 1);
		while ((int)ft_strlen(map->map[i]) < map->width)
			ft_strlcat(map->map[i], " ", map->width + 1);
		i++;
		index++;
	}
	map->map[i] = NULL;
	int t = 0;
	while (map->map[t])
	{
		printf("<<%s>>\n", map->map[t]);
		t++;
	}
}

int	edge(char *str)
{
	int i = -1;
	while (str[++i])
		if (!ft_strchr(" 1", str[i]))
			return (0);
	return(1);
}

void	check_closed(t_map *map)
{
	if (!edge(map->map[0]) || !edge(map->map[map->height - 1]))
		(printf("close your top or bottom\n"), exit(1));
}

void	check_player(t_map *map)
{
	int i = -1;
	int j = -1;
	int	player = 0;
	while(map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (ft_strchr("NEWS", map->map[i][j]))
			{
				if (!player)
				{
					player = 1;
					map->player_y = i;
					map->player_x = j;
					map->player = map->map[i][j];
				}
				else
					(printf("Broddie u can only have one\n"), exit(1));
			}
		}
	}
	if (!player)
		(printf("soo.... u dont wanna play?\n"), exit(1));
	// printf("player x:	%d\nplayer y:	%d\n", map->player_x, map->player_y);
}

void	no_void(t_map *map)
{
	int i = -1;
	int j = -1;
	
	char	invalid;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == ' ')
				invalid = '0';
			else if (map->map[i][j] == map->player)
				invalid = ' ';
			else if (map->map[i][j] == DOOR)
				invalid = ' ';
			else
				continue ;
			if (j > 0 && map->map[i][j - 1] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (j < map->width - 1 && map->map[i][j + 1] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (i > 0 && map->map[i - 1][j] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
			if (i < map->height - 1 && map->map[i + 1][j] == invalid)
				(printf("pos: x:%d\ny:%d\n\nyou cant go into the void bruv\n", j, i), exit(1));
		}
	}
}

void	parsing(char *path, t_game *game)
{
	int			index;
	t_file		file;

	index = 0;
	validate_file(path, &file);
	get_file(path, &file);
	index += get_textures(&file, &game->textures, game);
	if (!collected_textures(&game->textures))
		(printf("couldnt get them all\n"), exit(1));
	get_map(&file, &game->map, index);
	free_array(file.file);
	check_closed(&game->map);
	check_player(&game->map);
	no_void(&game->map);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		i;
	int		j;

	i = 0;
	if (ac != 2)
		(write(2, USAGE, ft_strlen(USAGE)), exit(1));
	game.mlx = mlx_init();
	parsing(av[1], &game);
	game.window = mlx_new_window(game.mlx, 500, 500, "cub test");
	while (i < 250)
	{
		j = 0;
		while (j < 500)
		{
			mlx_pixel_put(game.mlx, game.window, j, i, game.textures.ceiling);
			j++;
		}
		i++;
	}
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			mlx_pixel_put(game.mlx, game.window, j, i, game.textures.floor);
			j++;
		}
		i++;
	}
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.east, 0, 0);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.west, 250, 0);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.north, 0, 250);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.south, 250, 250);
	mlx_loop(game.mlx);
}
