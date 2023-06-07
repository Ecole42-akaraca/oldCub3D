/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:43:27 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/11 16:43:27 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_borders_inside(t_main *main)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (main->map[y])
	{
		while (main->map[y][x])
		{
			if (ft_strchr("0NSEW", main->map[y][x]) \
			&& (ft_strchr(" \0", main->map[y][x - 1]) \
			|| ft_strchr(" \0", main->map[y][x + 1]) \
			|| ft_strchr(" \0", main->map[y - 1][x - 1]) \
			|| ft_strchr(" \0", main->map[y - 1][x + 1]) \
			|| ft_strchr(" \0", main->map[y + 1][x - 1]) \
			|| ft_strchr(" \0", main->map[y + 1][x + 1])))
				return (err(YELLOW \
				"Map characters are used inappropriately!"END));
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	map_borders_left(t_main *main)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	while (main->map[y])
	{
		count = 0;
		while (main->map[y][x])
		{
			if (main->map[y][x] == '1')
				count++;
			else if (count == 0 && ft_strchr("0NSEW", main->map[y][x]))
				return (err(RED"Out-of-Bounds Argument: LEFT"END));
			x++;
		}
		x = 0;
		if (count == 0)
			return (err(RED"Empty Line: LEFT"END));
		y++;
	}
	return (0);
}

int	map_borders_bottom(t_main *main)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = main->max_y;
	while (main->map[y][x])
	{
		count = 0;
		while (y >= 0)
		{
			if (main->map[y][x] == '1')
				count++;
			else if (count == 0 && ft_strchr("0NSEW", main->map[y][x]))
				return (err(RED"Out-of-Bounds Argument: BOTTOM"END));
			y--;
		}
		y = main->max_y;
		if (count == 0)
			return (err(RED"Empty Line: BOTTOM"END));
		x++;
	}
	return (0);
}

int	map_borders_right(t_main *main)
{
	int	x;
	int	y;
	int	count;

	x = main->max_x;
	y = 0;
	while (main->map[y])
	{
		count = 0;
		while (x >= 0)
		{
			if (main->map[y][x] == '1')
				count++;
			else if (count == 0 && ft_strchr("0NSEW", main->map[y][x]))
				return (err(RED"Out-of-Bounds Argument: RIGHT"END));
			x--;
		}
		x = main->max_x;
		if (count == 0)
			return (err(RED"Empty Line: RIGHT"END));
		y++;
	}
	return (0);
}

int	map_borders_top(t_main *main)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	while (main->map[y][x])
	{
		count = 0;
		while (main->map[y] && main->map[y][x])
		{
			if (main->map[y][x] == '1')
				count++;
			else if (count == 0 && ft_strchr("0NSEW", main->map[y][x]))
				return (err(RED"Out-of-Bounds Argument: TOP"END));
			y++;
		}
		y = 0;
		if (count == 0)
			return (err(RED"Empty Line: TOP"END));
		x++;
	}
	return (0);
}
