/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:45:36 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/19 18:21:00 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	empty_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
	return (1);
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
				// printf("n: %s\ne: %s\nw: %s\ns: %s\nc: %d\nf: %d\n",
				// textures->north, textures->east, textures->west,
				// textures->south, textures->ceiling, textures->floor);
				(printf("%s: not a texture\n", file->file[i]), exit (1));
			}
	}
	while (file->file[i] && empty_line(file->file[i]))
		i++;
	printf("ceiling: %x\n", textures->ceiling);
	printf("floor: %x\n", textures->floor);
	return (i);
}
