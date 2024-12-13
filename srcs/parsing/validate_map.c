/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:08:02 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/13 10:08:14 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	empty_tile_is_valid(t_map *map, size_t x, size_t y)
{
	if (x == 0 || x == map->width || y == 0 || y == map->height)
		return (FALSE);
	if (map->grid[y - 1][x].id == VOID \
			|| map->grid[y + 1][x].id == VOID \
			|| map->grid[y][x - 1].id == VOID \
			|| map->grid[y][x + 1].id == VOID)
		return (FALSE);
	return (TRUE);
}

t_bool	map_is_valid(t_map *map)
{
	size_t	empty_tiles;
	size_t	x;
	size_t	y;

	if (map->start_direction == 0)
		return (FALSE);
	empty_tiles = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].id == EMPTY \
					&& empty_tile_is_valid(map, x, y))
				++empty_tiles;
			else if (map->grid[y][x].id == EMPTY)
				return (FALSE);
			++x;
		}
		++y;
	}
	if (empty_tiles == 0)
		return (FALSE);
	return (TRUE);
}
