/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:00:20 by gsever            #+#    #+#             */
/*   Updated: 2023/01/13 12:33:36 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief 
 * 
void put_pixel(double x, int y, double color, t_mlximg *img)//eskisi
{
	int	i;
	int	j;
	i = -1;
	while (++i < BOX_SIZE)
	{
		if (color == -123.0)
			break ;
		j = -1;
		while (++j < BOX_SIZE)
		{
			img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = color;
			if (j == BOX_SIZE - 1)
				img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = COLOR_TUNDORA;
		}
		if (i == BOX_SIZE - 1)
		{
			j = -1;
			while (++j < BOX_SIZE)
				img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = COLOR_TUNDORA;
		}
	}
}
 * 
 * @param x 
 * @param y 
 * @param color 
 * @param mini_map 
 * @param main 
 */
void	put_pixel(int x, int y, double color, t_main *main)//yenisi
{
	int	i;
	int	j;

	i = -1;
	while (++i < BOX_SIZE)
	{
		if (color == -123.0)
			break ;
		j = -1;
		while (++j < BOX_SIZE)
		{
			main->mini_map.addr[(int)((BOX_SIZE * (main->map.max_x + 1))
					* (y + i) + (x + j))] = color;
			if (j == BOX_SIZE - 1)
				main->mini_map.addr[(int)((BOX_SIZE * (main->map.max_x + 1))
						* (y + i) + (x + j))] = COLOR_TUNDORA;
		}
		if (i == BOX_SIZE - 1)
		{
			j = -1;
			while (++j < BOX_SIZE)
				main->mini_map.addr[(int)((BOX_SIZE * (main->map.max_x + 1))
						* (y + i) + (x + j))] = COLOR_TUNDORA;
		}
	}
}

// /**
//  * @brief Player's rotation_angle (one line) RED
//  * 
// void	draw_minimap_test(t_main *main)// eskisi
// {
// 	int	x;
// 	int y;
// 	y = -1;
// 	while (++y <= main->map.max_y)
// 	{
// 		x = -1;
// 		while (++x <= main->map.max_x)
// 		{
// 			if (main->map.map[y][x] == '1')
// 				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0xffffff, &(main->mini_map));
// 			else if (main->map.map[y][x] == '0')
// 				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0x000000, &(main->mini_map));
// 			// else
// 				// put_pixel(BOX_SIZE * x, BOX_SIZE * y, -123.0, &(main->img));
// 		}
// 	}
// }
//  * @param main 
//  */
// void	draw_player_directory(t_main *main)
// {
// 	double	ydy;
// 	double	ydx;
// 	double	ray_x;
// 	double	ray_y;
// 	double	dx;
// 	double	dy;

// 	ydy = sin((main->ply.rotation_angle + 180) * ONE_DEGREE);
// 	ydx = cos((main->ply.rotation_angle + 180) * ONE_DEGREE);
// 	ray_x = main->ply.pos_x;
// 	ray_y = main->ply.pos_y;
// 	dx = (main->ply.pos_x - ydx) - main->ply.pos_x;
// 	dy = (main->ply.pos_y + ydy) - main->ply.pos_y;
// 	while (1)
// 	{
// 		if (!is_wall(main, ray_x, ray_y))
// 			main->mini_map.addr[(BOX_SIZE * (main->map.max_x + 1))
// 				* (int)floor(BOX_SIZE * ray_y)
// 				+ (int)floor(BOX_SIZE * ray_x)] = COLOR_RED;
// 		else
// 			break;
// 		ray_x += dx / (WINDOW_H / 2);
// 		ray_y += dy / (WINDOW_H / 2);
// 	}
// 	//printf("x:%f y:%f\n", ray_x, ray_y);
// }

/**
 * @brief Player position with RED square.
 * 
 * @param main 
 */
void	draw_player_position(t_main *main)
{
	int	x;
	int	y;
	int	l;

	l = (BOX_SIZE / PLAYER_THICKNESS) / 2;
	y = -1 * l;
	while (y <= l)
	{
		x = -1 * l;
		while (x <= l)
		{
			main->mini_map.addr[(int)(BOX_SIZE * (main->map.max_x + 1))
				* (int)(BOX_SIZE * main->ply.pos_y + y)
				+ (int)(BOX_SIZE * main->ply.pos_x + x)] = COLOR_RED;
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_main *main)// yenisi
{
	int	x;
	int	y;
// int color = 255*(main->texture.rgb_c[0] * 65536) + (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];
	y = -1;
	while (++y <= main->map.max_y)
	{
		x = -1;
		while (++x <= main->map.max_x)
		{
			if (main->map.map[y][x] == '1')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y,
					COLOR_WHITE, main);
			else if (main->map.map[y][x] == '0')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y,
					COLOR_BLACK, main);
			else
				put_pixel(BOX_SIZE * x, BOX_SIZE * y,
					-123.0, main);
		}
	}
}