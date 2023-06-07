/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/18 17:15:54 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * 
 * Gerekli argler:
 * 	 Hangi duvara carptiginin bilinmesi gerekiyor;
 * 		dir_x, dir_y, hit_v, hit_h, hit_x, hit_y
 * bpp: 32, line_size: 256, endian: 0
 * @param main 
 * @param location 
 * @param color 
 */
void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
{
	int	i = -1;
	int find_pixel = 0;
	if (main->ray.hit_h == true)
		find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	else if (main->ray.hit_v == true)
		find_pixel = ((main->ray.pos_y - floor(main->ray.pos_y)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	int img_loc = (xpm.width * (xpm.height / 2)) + find_pixel;
	while (++i < oran)
	{
		if ((location - (WINDOW_W * i)) >= 0) //yukarı
			main->screen.addr[(location - (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];//xpm.img.addr[img_loc - (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))) // aşağı
			main->screen.addr[(location + (WINDOW_W * i))] = xpm.img.addr[img_loc + xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];//xpm.img.addr[img_loc + (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
	}
}
