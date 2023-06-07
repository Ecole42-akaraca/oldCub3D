/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:27:54 by akaraca           #+#    #+#             */
/*   Updated: 2023/01/09 11:36:50 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	linux_mlx_free(t_main *main)
{
	if (FREE_MLX == 1)
	{
		mlx_destroy_display(main->mlx.ptr);
		free(main->mlx.ptr);
	}
}

int ft_exit(t_main *main)
{
	free(main->texture.rgb_f);
	free(main->texture.rgb_c);
	free_definitions(main);
	free_pstr(main->map);
	mlx_destroy_image(main->mlx.ptr, main->screen.ptr);
	mlx_destroy_window(main->mlx.ptr, main->mlx.win);
	linux_mlx_free(main);
	exit(0);
}
