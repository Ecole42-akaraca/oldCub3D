/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:53:10 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/04 18:53:10 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author Ahmet KARACA (akaraca)
 * @author Görkem SEVER (gsever)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../includes/cub3d.h"

int	where_is_my_hero(int *x, int *y, t_main *main)
{
	(*y) = 0;
	while (main->map[*y])
	{
		(*x) = 0;
		while (main->map[*y][*x])
		{
			if (ft_strchr("ENWS", main->map[*y][*x]))
			{
				if (main->map[*y][*x] == 'E')
					main->ply.rotation_angle = 0;
				else if (main->map[*y][*x] == 'N')
					main->ply.rotation_angle = 90;
				else if (main->map[*y][*x] == 'W')
					main->ply.rotation_angle = 180;
				else if (main->map[*y][*x] == 'S')
					main->ply.rotation_angle = 270;
				main->map[*y][*x] = '0';
				return (0);
			}
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

/**
 * @brief	checking input arguments
 * 
 * @param argc	should be 2 arguments or else -> is error
 * @param map	if map name doesn't have .cub extension -> is error
 * 				if map name size < 5 (for "touch .cub")-> is error
 * 				if the specified file does not exist -> is error
 * @return int : Access 0, Error -1
 */
int	argv_check(int argc, char *map, t_main *main)
{
	int	fd;

	if (argc < 2)
		return (err(RED"Map argument unspecified!"END));
	if (argc > 2)
		return (err(RED"Too many arguments entered!"END));
	if (ft_strcmp_edited(".cub", &map[ft_strlen(map) - 4]) \
		|| ft_strlen(map) < 5 || map[ft_strlen(map) - 5] == '/')
		return (err(RED"Map extension is incorrect!"END));
	fd = open(map, F_OK);
	if (fd == -1)
		return (err(RED"Map argument doesn't exist!"END));
	return (map_check(fd, main));
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_main	main;

	if (argv_check(argc, argv[1], &main) != ERROR)
	{
		cub3d(&main);
		free(main.texture.rgb_f);
		free(main.texture.rgb_c);
		free_definitions(&main);
		free_pstr(main.map);
	}
	else
		return (1);
	return (0);
}
