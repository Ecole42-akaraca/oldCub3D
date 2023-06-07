/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:17:36 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/11 14:17:36 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*map_read(int fd)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		line = ft_strjoin(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (line);
}

int	map_check(int fd, t_main *main)
{
	char	*line;

	line = map_read(fd);
	if (!line)
		return (err(RED"Map is empty!"END));
	if (map_definitions(line, main) == ERROR)
	{
		free(line);
		return (ERROR);
	}
	else
		free(line);
	return (0);
}
