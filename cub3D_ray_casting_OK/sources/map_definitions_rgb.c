/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_definitions_rgb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:35:17 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/11 16:35:17 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_definitions_rgb_c(t_main *main)
{
	int	i;
	int	l;
	int	count;

	i = 0;
	l = 0;
	count = 0;
	while (main->texture.c[i] && count < 3)
	{
		if (main->texture.c[i] == ',' || main->texture.c[i + 1] == '\0')
		{
			main->l_free = ft_substr(main->texture.c, l, i);
			main->texture.rgb_c[count++] = ft_atoi(main->l_free);
			free(main->l_free);
			if (main->texture.rgb_c[count - 1] > 255)
				return (ERROR);
			l = i + 1;
		}
		i++;
	}
	if (main->texture.c[i] != '\0' || count != 3)
		return (ERROR);
	return (0);
}

int	map_definitions_rgb_f(t_main *main)
{
	int	i;
	int	l;
	int	count;

	i = 0;
	l = 0;
	count = 0;
	while (main->texture.f[i] && count < 3)
	{
		if (main->texture.f[i] == ',' || main->texture.f[i + 1] == '\0')
		{
			main->l_free = ft_substr(main->texture.f, l, i);
			main->texture.rgb_f[count++] = ft_atoi(main->l_free);
			free(main->l_free);
			if (main->texture.rgb_f[count - 1] > 255)
				return (ERROR);
			l = i + 1;
		}
		i++;
	}
	if (main->texture.f[i] != '\0' || count != 3)
		return (ERROR);
	return (0);
}

int	map_definitions_rgb(t_main *main)
{
	if (map_definitions_rgb_f(main) == ERROR)
	{
		free(main->texture.rgb_f);
		free(main->texture.rgb_c);
		return (err(RED"Map F extension is incorrect!"END));
	}
	if (map_definitions_rgb_c(main) == ERROR)
	{
		free(main->texture.rgb_f);
		free(main->texture.rgb_c);
		return (err(RED"Map C extension is incorrect!"END));
	}
	return (0);
}
