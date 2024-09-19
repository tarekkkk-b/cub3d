/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:00 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/19 15:24:53 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*****************************************************
*					libraries						*
*****************************************************/

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

/*****************************************************
*					definitions						*
*****************************************************/

# define WALL		'1'
# define FLOOR		'0'
# define NORTH		'N'
# define EAST		'E'
# define WEST		'W'
# define SOUTH		'S'
# define DOOR		'D'
# define USAGE		"Usage: ./cub3d [map_path].cub\n"
# define FILE_404	"File not found.\n"
# define TXTR_404	"Texture not found.\n"
# define EMPTY		"Empty file\n"
# define INVALID	"Invalid map file.\n"
# define INV_TXTR	"Invalid texture path\n"
# define XPM		"Invalid .xpm file\n"

/*****************************************************
*						structs						*
*****************************************************/

typedef struct s_file
{
	int		fd;
	int		file_size;
	char	**file;
}	t_file;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	int		player;
}	t_map;

typedef struct s_textures
{
	void	*north;
	void	*east;
	void	*west;
	void	*south;
	void	*floor_txtr;
	void	*ceiling_txtr;
	int		floor;
	int		f_arr[3];
	int		ceiling;
	int		c_arr[3];
}	t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_textures	textures;
}	t_game;


/*****************************************************
*					functions						*
*****************************************************/

int	minimap(t_game *game);
void	rendermap(t_game *game);

#endif