/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:00 by tabadawi          #+#    #+#             */
/*   Updated: 2024/09/14 21:21:57 by tabadawi         ###   ########.fr       */
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
# define USAGE		"Usage: ./cub3d [map_path].cub\n"
# define FILE_404	"File not found.\n"
# define EMPTY		"Empty file\n"
# define INVALID	"Invalid map file.\n"

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
}	t_map;

typedef struct s_textures
{
	void	*north;
	void	*east;
	void	*west;
	void	*south;
	int		floor;
	int		sky;
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

#endif