/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:00:25 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/19 16:35:42 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_mm(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 64)
	{
		j = x - 1;
		while (++j < x + 64)
			mlx_pixel_put(game->mlx, game->window, j, i, colour);
	}
}

void	draw_floor_mm(t_game *game, int x, int y, int colour)
{
	int j;
	int i  = y - 1;
	while (++i < y + 64)
	{
		j = x - 1;
		if (i == y || i == y + 64)
		{
			while (++j < x + 64)
			{
				mlx_pixel_put(game->mlx, game->window, j, i, colour);
				mlx_pixel_put(game->mlx, game->window, j, i + (i == y), colour);
				mlx_pixel_put(game->mlx, game->window, j, i - (i == y + 64), colour);
			}
		}
		else
		{
			mlx_pixel_put(game->mlx, game->window, j + 1, i, colour);
			mlx_pixel_put(game->mlx, game->window, j + 2, i, colour);
			mlx_pixel_put(game->mlx, game->window, j + 63, i, colour);
			mlx_pixel_put(game->mlx, game->window, j + 64, i, colour);
		}
	}
}

void	rendermap(t_game *game)
{
	int i = -1;
	int j;
	while (game->map.map[++i])
	{
		j = -1;
		while (game->map.map[i][++j])
		{
			if (game->map.map[i][j] == FLOOR || game->map.map[i][j] == DOOR || game->map.map[i][j] == game->map.player)
				draw_floor_mm(game, j * 64, i * 64, 0x4b7e94);
			else if (game->map.map[i][j] == WALL)
				draw_wall_mm(game, j * 64, i * 64, 0xb8bfc2);
			else if (game->map.map[i][j] == ' ')
				draw_wall_mm(game, j * 64, i * 64, 0xe34d52);
		}
	}
}

int	minimap(t_game *game)
{
	rendermap(game);
	return (1);
}