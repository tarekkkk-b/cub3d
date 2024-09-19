/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:48:16 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/19 16:24:35 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	arr = NULL;
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
		return (0);
	}
	fd = open(holder[1], O_RDONLY);
	if (fd == -1)
	{
		if (err_flag)
			write(2, TXTR_404, ft_strlen(TXTR_404));
		return (0);
	}
	close(fd);
	(*texture) = mlx_xpm_file_to_image(game->mlx, holder[1], &width, &height);
	if (!(*texture))
	{
		if (err_flag)
			write(2, XPM, ft_strlen(XPM));
		return (0);
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
