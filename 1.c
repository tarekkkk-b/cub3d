/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:21 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/18 21:29:38 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
