/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:07:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 15:55:28 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
map[y][x]
set map->grid[y][x]->entities to NULL
map->grid = get_grid(list);

valid map:
- 6 possible characters (0, 1, N, S, E or W)
- surrounded by walls (1)
- types of elements (except for map content) can be separated by 0+ empty line(s)
- types of elements (except for map content) can be set in any order in the file
- types of elements (except for map content) cam be separated by 0+ space(s)
*/
t_map	*parsing(char *path)
{
	t_parsing	parsing;

	init_parsing(&parsing);
	if (parsing.map == NULL)
		return (NULL);
	get_cub(&parsing, path);
	if (parsing.cub == NULL)
	{
		free_map(parsing.map);
		free_parsing(&parsing);
		return (NULL);
	}
	free_parsing(&parsing);
	return (parsing.map);
}
