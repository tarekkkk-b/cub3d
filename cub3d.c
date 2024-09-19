/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:21:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/19 18:28:12 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;
	int		i;
	// int		j;

	i = 0;
	if (ac != 2)
		(write(2, USAGE, ft_strlen(USAGE)), exit(1));
	game.mlx = mlx_init();
	parsing(av[1], &game);
	game.window = mlx_new_window(game.mlx, game.map.width * 64, game.map.height * 64, "cub test");
	mlx_loop_hook(game.mlx, minimap, &game);
	// rendermap(&game);
	// while (i < 250)
	// {
	// 	j = 0;
	// 	while (j < 500)
	// 	{
	// 		mlx_pixel_put(game.mlx, game.window, j, i, game.textures.ceiling);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// while (i < 500)
	// {
	// 	j = 0;
	// 	while (j < 500)
	// 	{
	// 		mlx_pixel_put(game.mlx, game.window, j, i, game.textures.floor);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.east, 0, 0);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.west, 250, 0);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.north, 0, 250);
	// mlx_put_image_to_window(game.mlx, game.window, game.textures.south, 250, 250);
	mlx_loop(game.mlx);
}
