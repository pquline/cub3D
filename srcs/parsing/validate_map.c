/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:08:02 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/06 13:55:34 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static t_bool	empty_tile_is_valid(t_map *map, size_t x, size_t y)
{
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		return (FALSE);
	return (map->grid[y - 1][x].id != VOID && map->grid[y + 1][x].id != VOID \
		&& map->grid[y][x - 1].id != VOID && map->grid[y][x + 1].id != VOID \
		&& map->grid[y - 1][x - 1].id != VOID \
		&& map->grid[y - 1][x + 1].id != VOID \
		&& map->grid[y + 1][x - 1].id != VOID \
		&& map->grid[y + 1][x + 1].id != VOID);
}

static t_bool	door_tile_is_valid(t_map *map, size_t x, size_t y)
{
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		return (parsing_error(ERR_DOOR_MISPLACED));
	if (map->grid[y - 1][x].id == EMPTY && map->grid[y + 1][x].id == EMPTY
			&& map->grid[y][x - 1].id == WALL && map->grid[y][x + 1].id == WALL)
		return (TRUE);
	else if (map->grid[y][x - 1].id == EMPTY && map->grid[y][x + 1].id == EMPTY
			&& map->grid[y - 1][x].id == WALL && map->grid[y + 1][x].id == WALL)
		return (TRUE);
	return (parsing_error(ERR_DOOR_MISPLACED));
}

static t_bool	map_row_is_valid(t_map *map, size_t y, size_t *empty_tiles)
{
	size_t	x;

	x = 0;
	while (x < map->width)
	{
		if (map->grid[y][x].id == DOOR \
				&& door_tile_is_valid(map, x, y) == FALSE)
			return (FALSE);
		if (map->grid[y][x].id == EMPTY && empty_tile_is_valid(map, x, y))
			++(*empty_tiles);
		else if (map->grid[y][x].id == EMPTY)
			return (parsing_error(ERR_NOT_SURROUNDED));
		++x;
	}
	return (TRUE);
}

t_bool	map_is_valid(t_map *map)
{
	size_t	empty_tiles;
	size_t	index;

	if (map->start_direction == 0)
		return (parsing_error(ERR_NO_PLAYER));
	empty_tiles = 0;
	index = 0;
	while (index < map->height)
	{
		if (map_row_is_valid(map, index, &empty_tiles) == FALSE)
			return (FALSE);
		++index;
	}
	if (empty_tiles == 0)
		return (parsing_error(ERR_NO_EMPTY));
	return (TRUE);
}
