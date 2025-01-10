/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:17:09 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 19:18:58 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <entities.h>

void	get_accessible_tiles(t_map *map, t_vector2 v)
{
	if (map->visited[v.y][v.x] == VISITED_TRUE \
			|| (map->grid[v.y][v.x].id != EMPTY \
			&& map->grid[v.y][v.x].id != DOOR))
		return ;
	map->visited[v.y][v.x] = VISITED_TRUE;
	get_accessible_tiles(map, (t_vector2){v.x - 1, v.y});
	get_accessible_tiles(map, (t_vector2){v.x + 1, v.y});
	get_accessible_tiles(map, (t_vector2){v.x, v.y - 1});
	get_accessible_tiles(map, (t_vector2){v.x, v.y + 1});
}

t_bool	init_accessible_map(t_map *map)
{
	size_t	index;

	map->visited = (t_visited **)ft_calloc(map->height, sizeof(t_visited *));
	if (map->visited == NULL)
		return (FAILURE);
	index = 0;
	while (index < map->height)
	{
		map->visited[index] = \
			(t_visited *)ft_calloc(map->width, sizeof(t_visited));
		if (map->visited[index] == NULL)
			return (free_double_array((void **)map->visited, index));
		++index;
	}
	return (SUCCESS);
}

t_bool	big_orb_can_spawn(t_map *map, t_vector2 min, t_vector2 max)
{
	t_vector2	save;

	if (min.x <= 0)
		min.x = 1;
	if (min.y <= 0)
		min.y = 1;
	save = min;
	if (max.x >= (int)map->width)
		max.x = map->width - 1;
	if (max.y >= (int)map->height)
		max.y = map->height - 1;
	while (min.y < max.y)
	{
		min.x = save.x;
		while (min.x < max.x)
		{
			if (map->visited[min.y][min.x] == VISITED_BIG_ORB)
				return (FALSE);
			++min.x;
		}
		++min.y;
	}
	return (TRUE);
}

static float	get_distance(size_t x, size_t y, t_vector2 v)
{
	const float	dx = (float)x - (float)v.x;
	const float	dy = (float)y - (float)v.y;

	return (sqrtf(dx * dx + dy * dy));
}

t_vector2	get_farthest_tile(t_map *map, t_vector2 player)
{
	t_vector2	curr;
	t_vector2	tile;
	float		distance;
	float		max;

	curr.y = 0;
	max = 0;
	tile = player;
	while (curr.y < (int)map->height)
	{
		curr.x = 0;
		while (curr.x < (int)map->width)
		{
			distance = get_distance(curr.x, curr.y, player);
			if (distance > max && map->visited[curr.y][curr.x] != VISITED_FALSE)
			{
				tile.x = curr.x;
				tile.y = curr.y;
				max = distance;
			}
			++curr.x;
		}
		++curr.y;
	}
	return (tile);
}
