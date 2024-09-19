/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:44:47 by ahashem           #+#    #+#             */
/*   Updated: 2024/09/18 21:24:43 by ahashem          ###   ########.fr       */
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
