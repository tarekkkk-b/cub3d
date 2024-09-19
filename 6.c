/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:50:39 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/18 21:37:07 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	edge(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr(" 1", str[i]))
			return (0);
	return (1);
}

void	check_closed(t_map *map)
{
	if (!edge(map->map[0]) || !edge(map->map[map->height - 1]))
		(printf("close your top or bottom\n"), exit(1));
}

void	check_player(t_map *map)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	j = -1;
	player = 0;
	while (map->map[++i])
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
	int		i;
	int		j;	
	char	invalid;

	i = -1;
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
