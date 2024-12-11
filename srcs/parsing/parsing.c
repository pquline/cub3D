/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:07:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 18:19:03 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
map[y][x]
valid map:
- 6 possible characters (0, 1, N, S, E or W)
- surrounded by walls (1)
- types of elements (except for map content) can be separated by 0+ empty line(s)
- types of elements (except for map content) can be set in any order in the file
- types of elements (except for map content) cam be separated by 0+ space(s)
*/

t_map	*parsing(char *path)
{
	t_map	*map;
	t_list	*list;

	map = init_map();
	if (map == NULL)
		return (NULL);
	list = get_cub(map, path);
	if (list == NULL)
		return (NULL);
	map->grid = get_grid(list);
}
