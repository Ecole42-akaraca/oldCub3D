/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:10:44 by gsever            #+#    #+#             */
/*   Updated: 2023/01/18 11:43:25 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_main *main)
{
	if (keycode == KEY_ESC)
	{
		// system("leaks cub3D");
		exit(0);//ft_free_and_close(); need add.
	}
	else if (keycode == KEY_W)
		main->key.value |= GO_FORWARD;
	else if (keycode == KEY_S)
		main->key.value |= GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key.value |= GO_RIGHT;
	else if (keycode == KEY_A)
		main->key.value |= GO_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key.value |= TURN_RIGHT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key.value |= TURN_LEFT;
	else if (keycode == KEY_ARROW_UP)
		main->key.value |= TURN_UP;
	else if (keycode == KEY_ARROW_DOWN)
		main->key.value |= TURN_DOWN;
	else if (keycode == KEY_R)
		set_player_default_pos(main);
	else if (keycode == KEY_L_SHIFT)
		main->ply.walk_speed = PLAYER_WALK_SPEED + 1.50;
	// printf("You press a key["B_CYAN"%d"END"]
	// & key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
	return (0);
}

int	key_release(int keycode, t_main *main)
{
	if (keycode == KEY_W)
		main->key.value &= ~GO_FORWARD;
	else if (keycode == KEY_S)
		main->key.value &= ~GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key.value &= ~GO_RIGHT;
	else if (keycode == KEY_A)
		main->key.value &= ~GO_LEFT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key.value &= ~TURN_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key.value &= ~TURN_RIGHT;
	else if (keycode == KEY_ARROW_UP)
		main->key.value &= ~TURN_UP;
	else if (keycode == KEY_ARROW_DOWN)
		main->key.value &= ~TURN_DOWN;
	else if (keycode == KEY_L_SHIFT)
		main->ply.walk_speed = PLAYER_WALK_SPEED;
	else if (keycode == KEY_SPACE)
		main->mouse.is_enable = true;
	// printf("You removed a key["B_BLUE"%d"END"]
	// & key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
	return (0);
}

int	mouse_move(int x, int y, t_main *main)
{
	if (main->mouse.is_enable)
	{
		main->ply.rotation_angle = -1.0 * (x % 360);
		main->key.screen_mid = -1.0 * (y % WINDOW_H);
		printf("mouse:x[%d] y[%d]\n", x, y);
	}
	return (0);
}