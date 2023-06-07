/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_definitions_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:31:38 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/11 16:31:38 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_definitions_check_rgb(t_main *main)
{
	int		i;

	i = 0;
	while (main->texture.f[i] && ft_strchr(RGB_CHR, main->texture.f[i]))
		i++;
	if (main->texture.f[i] != '\0')
		return (err(RED"Map F extension is incorrect!"END));
	i = 0;
	while (main->texture.c[i] && ft_strchr(RGB_CHR, main->texture.c[i]))
		i++;
	if (main->texture.c[i] != '\0')
		return (err(RED"Map C extension is incorrect!"END));
	main->texture.rgb_f = (int *)malloc(sizeof(int) * 3);
	if (!main->texture.rgb_f)
		return (err(RED"Cannot allocate memory!"END));
	main->texture.rgb_c = (int *)malloc(sizeof(int) * 3);
	if (!main->texture.rgb_c)
	{
		free(main->texture.rgb_f);
		return (err(RED"Cannot allocate memory!"END));
	}
	return (map_definitions_rgb(main));
}

int	xpm_file_check(char *str, char *name)
{
	int	fd;

	if (ft_strcmp_edited(".xpm", &str[ft_strlen(str) - 4]) \
		|| ft_strlen(str) < 5 || str[ft_strlen(str) - 5] == '/')
	{
		write(2, RED, ft_strlen(RED));
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
		return (err(RED"File extension is incorrect!"END));
	}
	fd = open(str, F_OK);
	if (fd == -1)
	{
		write(2, RED, ft_strlen(RED));
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
		return (err(RED"File does not exist!"END));
	}
	close(fd);
	return (0);
}

int	map_definitions_check(int count, char *line, int limit, t_main *main)
{
	if (count != 6 \
	|| !main->texture.no || !main->texture.so \
	|| !main->texture.we || !main->texture.ea \
	|| !main->texture.f || !main->texture.c)
	{
		free_definitions(main);
		return (err(RED"Map definitions are missing or incorrect!"END));
	}
	if (xpm_file_check(main->texture.no, "NO") == ERROR \
	|| xpm_file_check(main->texture.so, "SO") == ERROR \
	|| xpm_file_check(main->texture.we, "WE") == ERROR \
	|| xpm_file_check(main->texture.ea, "EA") == ERROR)
	{
		free_definitions(main);
		return (ERROR);
	}
	if (map_definitions_check_rgb(main) == ERROR)
	{
		free_definitions(main);
		return (ERROR);
	}
	return (map_map(line, limit, main));
}
