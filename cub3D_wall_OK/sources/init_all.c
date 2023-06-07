/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:45:58 by gsever            #+#    #+#             */
/*   Updated: 2023/01/17 15:41:41 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_all_xpm_files(t_main *main)
{
	int	i;
	main->xpm[0].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
		main->texture.no, &main->xpm[0].width, &main->xpm[0].height);
	main->xpm[1].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
		main->texture.so, &main->xpm[1].width, &main->xpm[1].height);
	main->xpm[2].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
		main->texture.ea, &main->xpm[2].width, &main->xpm[2].height);
	main->xpm[3].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
		main->texture.we, &main->xpm[3].width, &main->xpm[3].height);
	i = -1;
	while (++i < 4)
		main->xpm[i].img.addr = (int *)mlx_get_data_addr(main->xpm[i].img.ptr,
			&main->xpm[i].img.bpp, &main->xpm[i].img.line_size,
			&main->xpm[i].img.endian);
	return (0);
}

static int	init_mlx_draw(t_main *main)
{
	init_set_player(main, 0, 0);
	main->ply.walk_speed = PLAYER_WALK_SPEED;
	main->key.screen_mid = (WINDOW_H / 2);
	main->key.value = 0;
	main->mouse.is_enable = false;
	return (0);
}

static int	init_minimap_image(t_main *main)
{
	main->mini_map.ptr = mlx_new_image(main->mlx.ptr, BOX_SIZE
		* (main->map.max_x + 1), BOX_SIZE * (main->map.max_y + 1));
	if (main->mini_map.ptr == NULL)
		return (print_error(PROMPT, "minimap", "mlx_new_image()", "error."));
	main->mini_map.addr = (int *)mlx_get_data_addr(main->mini_map.ptr, &main->mini_map.bpp,
			&main->mini_map.line_size, &main->mini_map.endian);
	if (main->mini_map.addr == NULL)
		return (print_error(PROMPT, "minimap",
			"mlx_get_data_addr()", "error."));
	return (0);
}

static int	init_minimap(t_main *main)
{
	if (init_minimap_image(main) == ERROR)// image init area
		return (ERROR);
	return (0);
}

static int	init_cub3d_image(t_main *main)
{
	main->screen.ptr = mlx_new_image(main->mlx.ptr, (int)(WINDOW_W), (int)(WINDOW_H));
	if (main->screen.ptr == NULL)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.win);
		linux_mlx_free(main);
		return (print_error(PROMPT, "mlx", "mlx_new_image()", "error."));
	}
	main->screen.addr = (int *)mlx_get_data_addr(main->screen.ptr, &main->screen.bpp,
			&main->screen.line_size, &main->screen.endian);
	if (main->screen.addr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_get_data_addr()", "error."));
	return (0);
}

static int	init_cub3d_window(t_main *main)
{
	main->mlx.win = mlx_new_window(main->mlx.ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (main->mlx.win == NULL)
	{
		linux_mlx_free(main);
		return (print_error(PROMPT, "mlx", "mlx_new_window()", "error."));
	}
	return (0);
}

static int	init_cub3d(t_main *main)
{
	main->mlx.ptr = mlx_init();
	if (main->mlx.ptr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_init()", "error."));
	if (init_cub3d_window(main) == ERROR)// window init area
		return (ERROR);
	if (init_cub3d_image(main) == ERROR)// image init area (screen)
		return (ERROR);
	return (0);
}

int	init_all(t_main *main)
{
	if (init_cub3d(main) == ERROR)// malloc init area
		return (ERROR);
	if (init_minimap(main) == ERROR)// image init area
		return (ERROR);
	if (init_mlx_draw(main) == ERROR)// ply_location...
		return (ERROR);
	if (init_all_xpm_files(main) == ERROR)// xpm file to img.
		return (ERROR);
	return (0);
}