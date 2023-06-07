/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_definitions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:17:20 by akaraca           #+#    #+#             */
/*   Updated: 2022/11/11 14:17:20 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_definitions(t_main *main)
{
	if (main->texture.no != NULL)
		free(main->texture.no);
	if (main->texture.so != NULL)
		free(main->texture.so);
	if (main->texture.we != NULL)
		free(main->texture.we);
	if (main->texture.ea != NULL)
		free(main->texture.ea);
	if (main->texture.f != NULL)
		free(main->texture.f);
	if (main->texture.c != NULL)
		free(main->texture.c);
}

int	map_definitions_invalid_input(char *line, int limit, t_main *main)
{
	if (!ft_strchr(MAP_WHITESPACES, line[limit]))
	{
		free_definitions(main);
		return (ERROR);
	}
	return (0);
}

char	*map_read_definitions(char *line, int *limit, int *count, int size)
{
	int		i;
	char	*str;

	str = NULL; 
	if ((*limit) == 0 || line[(*limit) - 1] == '\n')
	{
		(*count)++;
		*limit = (*limit) + size;
		while (line[*limit] && (line[*limit] == ' ' || line[*limit] == '\t'))
			(*limit)++;
		i = *limit;
		while (line[i] && !ft_strchr(WHITESPACES, line[i]))
			i++;
		if (line[i] == '\n' || line[i] == '\r')
			i--;
		else
			return (NULL);
		if (i > (*limit) + 3)
			str = ft_substr(&line[*limit], 0, ++i - (*limit));
		else
			return (NULL);
		*limit = i;
	}
	return (str);
}

void	map_definitions_init(t_main *main)
{
	main->texture.no = NULL;
	main->texture.so = NULL;
	main->texture.we = NULL;
	main->texture.ea = NULL;
	main->texture.f = NULL;
	main->texture.c = NULL;
}

/**
 * @brief	Map definitions read first entries, Don't repeat entries!
 *			Skipped if there are different entries before definitions.
 * @param line 
 * @param main 
 * @return int 
 */
int	map_definitions(char *line, t_main *main)
{
	int	count;
	int	limit;

	limit = 0;
	count = 0;
	map_definitions_init(main);
	while (line[limit] && count < 6)
	{
		if (!main->texture.no && ft_strncmp_edited("NO ", &line[limit], 3))
			main->texture.no = map_read_definitions(line, &limit, &count, 3);
		if (!main->texture.so && ft_strncmp_edited("SO ", &line[limit], 3))
			main->texture.so = map_read_definitions(line, &limit, &count, 3);
		if (!main->texture.we && ft_strncmp_edited("WE ", &line[limit], 3))
			main->texture.we = map_read_definitions(line, &limit, &count, 3);
		if (!main->texture.ea && ft_strncmp_edited("EA ", &line[limit], 3))
			main->texture.ea = map_read_definitions(line, &limit, &count, 3);
		if (!main->texture.f && ft_strncmp_edited("F ", &line[limit], 2))
			main->texture.f = map_read_definitions(line, &limit, &count, 2);
		if (!main->texture.c && ft_strncmp_edited("C ", &line[limit], 2))
			main->texture.c = map_read_definitions(line, &limit, &count, 2);
		if (map_definitions_invalid_input(line, limit, main) == ERROR)
			return (err(RED"Invalid input!"END));
		limit++;
	}
	return (map_definitions_check(count, line, limit, main));
}
