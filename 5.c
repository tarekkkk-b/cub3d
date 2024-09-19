/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:49:40 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/19 17:30:44 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_line(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr("10NEWSD ", str[i]))
			(printf("BAD ELEMENT\n"), exit(1));
	return (1);
}

void	check_len(int index, t_map *map, t_file *file)
{
	int	empty;
	int	width;

	empty = 0;
	width = 0;
	while (file->file[index] && empty_line(file->file[index]))
		index++;
	map->width = ft_strlen(file->file[index]);
	while (file->file[index] && map_line(file->file[index]))
	{
		width = ft_strlen(file->file[index]);
		if (width > map->width)
			map->width = width;
		// printf("line:	<<%s>>	length:	%zu\n", file->file[index],
		// ft_strlen(file->file[index]));
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
	// return (map->height);
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player = 0;
}

void	get_map(t_file *file, t_map *map, int index)
{
	int	i;
	int	t;

	init_map(map);
	check_len(index, map, file);
	if (map->height == -1 || map->height < 3)
		(printf("womp womp map problem\n"), exit(1));
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		exit(1);
	while (file->file[index] && empty_line(file->file[index]))
		index++;
	i = 0;
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
	t = 0;
	while (map->map[t])
	{
		printf("<<%s>>\n", map->map[t]);
		t++;
	}
}
