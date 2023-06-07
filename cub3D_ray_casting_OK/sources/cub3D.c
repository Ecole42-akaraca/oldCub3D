/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:55:29 by akaraca           #+#    #+#             */
/*   Updated: 2022/12/07 19:55:29 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall(double x, double y, t_main *main)
{
	int xX;
	int yY;

	if (x < 0 || x > main->max_x || y < 0 || y > main->max_y)
		return (1);
    xX = floor(x);
    yY = floor(y);
	if (main->map[yY][xX] != '1')
		return (0);
    return (1);
}

void put_pixel(double x, int y, double color, t_mini_map *mini_map, t_main *main)
{
	int i;
	int j;

	i = -1;
	while (++i < BOX_SIZE)
	{
		j = -1;
		while (++j < BOX_SIZE)
		{
			mini_map->addr[(int)((BOX_SIZE * (main->max_x+1)) * (y + i) + (x + j))] = color;
			//mini_map->addr[(int)(WINDOW_W * (y + i) + (x + j))] = color;
		}
	}
}

void	draw_minimap_test(t_main *main)
{
	int	x;
	int y;
	int color = 255*(main->texture.rgb_c[0] * 65536) + (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];
	y = -1;
	while (++y <= main->max_y)
	{
		x = -1;
		while (++x <= main->max_x)
		{
			if (main->map[y][x] == '1')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0xffffff, &(main->mini_map), main);
			else if (main->map[y][x] == '0')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0x000000, &(main->mini_map), main);
			else
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, color, &(main->mini_map), main);
		}
	}
}

void	draw_player_test(t_main *main)
{
	int	x;
	int	y;
	int l;

	l = main->ply.thickness / 2;
	y = -1 * l;
	while (y <= l)
	{
		x = -1 * l;
		while (x <= l)
		{
			main->mini_map.addr[(int)(BOX_SIZE * (main->max_x+1)) * (int)(BOX_SIZE * main->ply.y + y) + (int)(BOX_SIZE * main->ply.x + x)] = 0xff0000;
			x++;
		}
		y++;
	}
}

void	draw_player_directory(t_main *main)
{
	double ydy;
	double ydx;
	ydy = 1 * sin((main->ply.rotation_angle + 180) * (PI / 180));
	ydx = 1 * cos((main->ply.rotation_angle + 180) * (PI / 180));
    double    ray_x;
    double    ray_y;
    double    dx;
    double    dy;
    double    max_value;
    
    ray_x = main->ply.x;
    ray_y = main->ply.y;
    dx = (main->ply.x - ydx) - main->ply.x;
    dy = (main->ply.y + ydy) - main->ply.y;

    max_value = fmax(fabs(dx), fabs(dy));
    dx /= max_value;
    dy /= max_value;
    while (1)
    {
        if (!is_wall(ray_x, ray_y, main))
            main->mini_map.addr[(BOX_SIZE * (main->max_x+1)) * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = 0xff0000;
        else
            break;
        ray_x += dx / 2000;
        ray_y += dy / 2000;
    }
	//printf("x:%f y:%f\n", ray_x, ray_y);
}

int is_wall_v2(double x, double y, t_main *main)
{
	int xX;
	int yY;

	xX = (int)floor(x);
	yY = (int)floor(y);
	return (ft_strchr("0NSEW", main->map[yY][xX]) == NULL);
}

double	ray_vertical(t_main *main, double angle, double dir_x, double dir_y, bool *hit)
{
	double vdy;
	double vdx;

	if (dir_x == -1)
		vdx = main->ply.x - floor(main->ply.x);
	else
		vdx = ceil(main->ply.x) - main->ply.x;
	vdy = fabs(tan(angle * (PI / 180)) * vdx);

	double tmp_x = vdx*dir_x;
	double tmp_y = vdy*dir_y;
	// printf("Box:Vx: %f Vy:%f\n", tmp_x, tmp_y);
	while (main->ply.x + vdx*dir_x - 0.0001 >= 0 && main->ply.x + vdx*dir_x - 0.0001 <= main->max_x
	&& main->ply.y + vdy*dir_y >= 0 && main->ply.y + vdy*dir_y <= main->max_y)
	{
		// printf("---\n");
		vdx = vdx + 0.0001;
		if (is_wall_v2(main->ply.x + vdx*dir_x, main->ply.y + vdy*dir_y, main))
		{
			*hit = true;
			// printf("V:ture\n");
			// vdx = vdx - 0.0001;
			// vdy = fabs(tan(angle * (PI / 180)) * vdx);
			tmp_x = vdx*dir_x;
			tmp_y = vdy*dir_y;
			// printf("Vx: %f Vy:%f\n", tmp_x, tmp_y);
			// printf("Px: %f Py:%f\n", main->ply.x, main->ply.y);
			// printf("V-Location: x: %f y: %f\n", main->ply.x + vdx*dir_x, main->ply.y + vdy*dir_y);
			break;
		}
		vdx = vdx + 1 - 0.0001;
		vdy = fabs(tan(angle * (PI / 180)) * vdx);
	}
	double distance;
	if (*hit == true)
		distance = sqrt((tmp_x*tmp_x) + (tmp_y*tmp_y));
	else
		distance = 10000;
	return (distance);
}

double ray_horizonal(t_main *main, double angle, double dir_x, double dir_y, bool *hit)
{
	double hdy;
	double hdx;

	if (dir_y == -1)
		hdy = main->ply.y - floor(main->ply.y);
	else
		hdy = ceil(main->ply.y) - main->ply.y;
	hdx = fabs(hdy / tan(angle * (PI / 180)));

	double tmp_y = hdy*dir_y;
	double tmp_x = hdx*dir_x;
	// printf("Box:Hx: %f Hy:%f\n", tmp_x, tmp_y);
	while (main->ply.x + hdx*dir_x >= 0 && main->ply.x + hdx*dir_x <= main->max_x
	&& main->ply.y + hdy*dir_y - 0.0001 >= 0 && main->ply.y + hdy*dir_y - 0.0001 <= main->max_y)
	{
	// printf("---\n");
		hdy = hdy + 0.0001;
		if (is_wall_v2(main->ply.x + hdx*dir_x, main->ply.y + hdy*dir_y, main))
		{
			*hit = true;
		// printf("H:ture\n");
			// hdy = hdy - 0.0001;
			// hdx = fabs(hdy / tan(angle * (PI / 180)));
			tmp_x = hdx*dir_x;
			tmp_y = hdy*dir_y;
		// printf("Hx: %f Hy:%f\n", tmp_x, tmp_y);
		// printf("Px: %f Py:%f\n", main->ply.x, main->ply.y);
		// printf("H-Location: x: %f y: %f\n", main->ply.x + hdx*dir_x, main->ply.y + hdy*dir_y);
			break;
		}
		hdy = hdy + 1 - 0.0001;
		hdx = fabs(hdy / tan(angle * (PI / 180)));
	}

	double distance;
	if (*hit == true)
		distance = sqrt((tmp_x*tmp_x) + (tmp_y*tmp_y));
	else
		distance = 10000;
	return (distance);
}

void _3D(t_main *main, double distance, int ray_count)
{
	int loc;
	int mid;
	double oran;
	int	i;
	int color;
	distance = distance * (double)BOX_SIZE * ((double)WINDOW_H / (double)WINDOW_W);
	i = 0;
	mid = WINDOW_H / 2.0;
	loc = (WINDOW_W * mid) - ray_count;
	oran = (((double)WINDOW_H / 2.0) / distance) * (double)BOX_SIZE;

	int darkness = 1;//20;
	// if (distance <= 50)
	// 	darkness = 10;
	if (main->test._hith == true)
		color = 0x400000 * darkness;
	else if (main->test._hitv == true)
		color = 0x000040 * darkness;
	else
		color = 0x00ff00; //error
	while (i <= oran && i <= (WINDOW_H / 2.0) - 1.0)
	{
		//main->screen.addr[(loc + (WINDOW_W * i))] = main->test.img_addr[(16 * x)];//color;
		main->screen.addr[(loc + (WINDOW_W * i))] = color;
		main->screen.addr[(loc - (WINDOW_W * i))] = color;
		i++;
	}
}

void draw_ray(double distance, int dir_x, int dir_y, t_main *main, double angle, int ray_count, double original_dist)
{
    double    ray_x;
    double    ray_y;
    double    dx;
    double    dy;

    ray_x = main->ply.x;
    ray_y = main->ply.y;
    dx = distance * fabs(cos(angle * (PI / 180))) * dir_x;
    dy = distance * fabs(sin(angle * (PI / 180))) * dir_y;
    while (1)
    {
        if (!is_wall(ray_x, ray_y, main) && (sqrt(((main->ply.x - ray_x)*(main->ply.x - ray_x)) + ((main->ply.y - ray_y)*(main->ply.y - ray_y))) <= original_dist))
            main->mini_map.addr[(BOX_SIZE * (main->max_x +1)) * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = 0x00ff00;
        else
		{
			//printf("%f -- %f\n", sqrt(((main->ply.x - ray_x)*(main->ply.x - ray_x)) + ((main->ply.y - ray_y)*(main->ply.y - ray_y))), original_dist);
			_3D(main, distance, ray_count);
            break;
		}
        ray_x += dx / (WINDOW_H / 2);
        ray_y += dy / (WINDOW_H / 2);
    }
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	int dir_x = ((cos(angle * (PI / 180)) > 0) * 2) - 1;
	int dir_y = ((sin(angle * (PI / 180)) > 0) * -2) + 1;
	double distance_v;
	double distance_h;
	double distance;
	bool hitv = false;
	bool hith = false;
	distance_v = ray_vertical(main, angle, dir_x, dir_y, &hitv); //dikey
	distance_h = ray_horizonal(main, angle, dir_x, dir_y, &hith); //yatay
	// printf("V: %f H:%f\n", distance_v, distance_h);
//**************************************************************************************
	// if ((hitv == true && hith == true) || (hitv == false && hith == false))
	// {
	// 	if (distance_v < distance_h)
	// 		distance = distance_v;
	// 	else
	// 		distance = distance_h;
	// }
	// else if (hitv == false && hith == true)
	// 	distance = distance_h;
	// else
	// 	distance = distance_v;
//**************************************************************************************
	if (distance_v < distance_h)
	{
		distance = distance_v;
		main->test._hith = false;
		main->test._hitv = true;
	}
	else
	{
		distance = distance_h;
		main->test._hith = true;
		main->test._hitv = false;
	}
	double original_dist = distance;
	distance = distance * fabs(cos((main->ply.rotation_angle - angle) * (PI / 180)));
//**************************************************************************************
// main->test._dir_x = dir_x;
// main->test._dir_y = dir_y;
// main->test._hith = hith;
// main->test._hitv = hitv;
	draw_ray(distance, dir_x, dir_y, main, angle, ray_count, original_dist);
}

void	draw_background( t_main *main)
{
//White RGB code = 255*65536+255*256+255 = #FFFFFF        başına bitanadaha koy şaffaflığ ıçın
	int	y = 0;
	int ceil = (main->texture.rgb_c[0] * 65536) + (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];
	int floor = (main->texture.rgb_f[0] * 65536) + (main->texture.rgb_f[1] * 256) + main->texture.rgb_f[2];
//	printf("ceil: %d floor: %d\n", ceil, floor);
	while (y < WINDOW_H / 2)
	{
		int x = 0;
		while (x < WINDOW_W)
		{
			main->screen.addr[WINDOW_W * y + x] = ceil;
			x++;
		}
		y++;
	}
	while (y < WINDOW_H)
	{
		int x = 0;
		while (x < WINDOW_W)
		{
			main->screen.addr[WINDOW_W * y + x] = floor;
			x++;
		}
		y++;
	}
}

int	ft_loop(t_main *main)
{
	// long i = 100000;
	// while (i > 0)
	// 	i--;
	draw_background(main);
	key_function(main);
	draw_minimap_test(main);
	draw_player_test(main);


	double angle;
	angle = -1 * (FOV / 2.0);
	int ray_count = 0;
	while (angle <= (FOV / 2.0))
	{
		raycasting(main, main->ply.rotation_angle + angle, ray_count);
		angle += (FOV / 2.0) / ((FOV_THICKNESS - 1) / 2.0);
		ray_count++;
	}
	// raycasting(main, main->ply.rotation_angle, (FOV_THICKNESS - 1)/2);

	draw_player_directory(main);

	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->screen.ptr, 0, 0);
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->mini_map.ptr, 0, 0);
	return (0);
}

void	cub3d(t_main *main)
{
	if (minilibx_init(main) != ERROR)
	{
		int height;
		int width;
		main->test.img = mlx_xpm_file_to_image(main->mlx.ptr, main->texture.no, &width, &height);
		main->test.img_addr = (int *)mlx_get_data_addr(main->test.img, &main->test.bpp, &main->test.line_size, &main->test.endian);
		int	x;
		int	y;

		where_is_my_hero(&x, &y, main);
		main->ply.x = x + 0.5;
		main->ply.y = y + 0.5;
		main->ply.thickness = BOX_SIZE / PLAYER_THICKNESS;
		main->ply.walk_speed = PLAYER_WALKSPEED;
		// printf("MAX_X:%d MAX_Y:%d\n", main->max_x, main->max_y);
		// printf("ply_x:%f ply_y:%f\n", main->ply.x, main->ply.y);

		main->key.left = false;
		main->key.right = false;
		main->key.up = false;
		main->key.down = false;
		main->key.r_left = false;
		main->key.r_right = false;

		mlx_loop_hook(main->mlx.ptr, ft_loop, main);
		mlx_hook(main->mlx.win, 2, 1L<<0, &key_press, main);
		mlx_hook(main->mlx.win, 3, 1L<<1, &key_release, main);
		mlx_hook(main->mlx.win, 17, (0L), &ft_exit, main);
		mlx_loop(main->mlx.ptr);
	}
}
