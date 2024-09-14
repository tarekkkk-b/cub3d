/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/14 21:27:50 by tabadawi         ###   ########.fr       */
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
		&& textures->sky != -1)
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
	textures->sky = -1;
	textures->floor = -1;
}

void	assign_texture(char *str, void **texture, void	*mlx)
{
	char	**holder;
	int height, width;

	holder = ft_split(str, ' ');
	if (!holder[0] || !holder[1] || holder[2])
		(printf("extra thing in texture\n"), free_array(holder), exit(1));
	int	fd;
	fd = open(holder[1], O_RDONLY);
	if (fd == -1)
		(printf("no file to open\n"), free_array(holder), exit(1));
	close(fd);
	texture = mlx_xpm_file_to_image(mlx, holder[1], &width, &height);
	if (!texture)
		(printf("no xpm\n"), exit(1));
	free_array(holder);
}

void	assign_colour(int *colour)
{
	(*colour) = 1;
}

int	check_texture(char *str, t_textures *textures, void	*mlx)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == NORTH && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, &textures->north, mlx);
	else if (str[i] == SOUTH && str[i + 1] == 'O' && str[i + 2] == ' ')
		assign_texture(str, &textures->south, mlx);
	else if (str[i] == WEST && str[i + 1] == 'E' && str[i + 2] == ' ')
		assign_texture(str, &textures->west, mlx);
	else if (str[i] == EAST && str[i + 1] == 'A' && str[i + 2] == ' ')
		assign_texture(str, &textures->east, mlx);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		assign_colour(&textures->sky);
	else if (str[i] == 'F' && str[i + 1] == ' ')
		assign_colour(&textures->floor);
	else
		return (0);
	return (1);
}

int	get_textures(t_file *file, t_textures *textures, void *mlx)
{
	int	i;

	i = -1;
	init_textures(textures);
	while (file->file[++i])
	{
		if (!empty_line(file->file[i]))
			if (!check_texture(file->file[i], textures, mlx))
				(printf("not a texture\n"), exit (1));

		if (collected_textures(textures))
			break ;
	}
	while (file->file[i] && empty_line(file->file[i]))
		i++;
	i++;
	return (i);
}

void	parsing(char *path, t_game *game)
{
	int			index;
	t_file		file;

	index = 0;
	validate_file(path, &file);
	get_file(path, &file);
	index += get_textures(&file, &game->textures, game->mlx);
	printf("%d\n", index);
	if (!collected_textures(&game->textures))
		(printf("couldnt get them all\n"), exit(1));
	// get_map(&file, map, index);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		(write(2, USAGE, ft_strlen(USAGE)), exit(1));
	game.mlx = mlx_init();
	parsing(av[1], &game);
}
