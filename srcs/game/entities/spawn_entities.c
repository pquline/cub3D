/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/06 15:26:46 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static size_t	get_accessible_tiles_count(t_map *map, t_vector2 v, \
	size_t count)
{
	if (map->visited[v.y][v.x] == TRUE || map->grid[v.y][v.x].id != EMPTY)
		return (0);
	map->visited[v.y][v.x] = TRUE;
	return (
		get_accessible_tiles_count(map, (t_vector2){v.x - 1, v.y}, count) \
		+ get_accessible_tiles_count(map, (t_vector2){v.x + 1, v.y}, count) \
		+ get_accessible_tiles_count(map, (t_vector2){v.x, v.y - 1}, count) \
		+ get_accessible_tiles_count(map, (t_vector2){v.x, v.y + 1}, count) + 1);
}

static t_bool	init_visited_map(t_map *map)
{
	size_t	index;

	map->visited = (t_bool **)ft_calloc(map->height, sizeof(t_bool *));
	if (map->visited == NULL)
		return (FAILURE);
	index = 0;
	while (index < map->height)
	{
		map->visited[index] = (t_bool *)ft_calloc(map->width, sizeof(t_bool));
		if (map->visited[index] == NULL)
			return (free_double_array((void **)map->visited, index));
		++index;
	}
	return (SUCCESS);
}

t_bool	spawn_coin_entities(t_game *game, t_map *map)
{
	t_entity	*coin;
	t_vector2	v;

	v.y = 0;
	while ((size_t)v.y < map->height)
	{
		v.x = 0;
		while ((size_t)v.x < map->width)
		{
			if (map->visited[v.y][v.x] == TRUE \
				&& !(v.x == map->start_coords.x && v.y == map->start_coords.y))
			{
				coin = spawn_entity(game, &orbe_update, &orbe_minimap, NULL);
				if (coin == NULL)
					return (FAILURE);
				set_entity_pos(coin, (float)v.x + 0.5, (float)v.y + 0.5);
			}
			++v.x;
		}
		++v.y;
	}
	return (SUCCESS);
}

/*
static t_bool	spawn_coin_entities(t_game *game)
{
	bool			visited[game->engine.map->height][game->engine.map->width];

	ft_bzero(visited, game->engine.map->height * game->engine.map->width);
	const size_t	count = get_accessible_tiles_count(game->engine.map->grid, \
		game->engine.map->start_coords, visited, 0) / 2 - 1;

	dprintf(2, "count = %zu\n", count);
	return (SUCCESS);
}
*/

static t_vector2	get_farthest_tile(t_game *game, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(void)game;
	(void)map;
	return ((t_vector2){x, y});
}

static t_bool	spawn_enemy_entities(t_game *game, t_map *map)
{
	size_t		index;
	t_entity	*enemy;
	t_vector2	pos;

	pos = get_farthest_tile(game, map);
	index = 0;
	while (index < 4)
	{
		enemy = spawn_entity(game, &ghost_update, &ghost_minimap, NULL);
		if (enemy == NULL)
			return (FAILURE);
		set_entity_pos(enemy, (float)pos.x + 0.5, (float)pos.y + 0.5);
		++index;
	}
	return (SUCCESS);
}

t_bool	spawn_entities(t_game *game)
{
	size_t		count;
	t_entity	*player;

	player = spawn_entity(game, &player_update, &player_minimap, NULL);
	if (player == NULL)
		return (FAILURE);
	if (init_visited_map(game->engine.map) == FAILURE)
		return (FAILURE);
	count = get_accessible_tiles_count(game->engine.map, \
		game->engine.map->start_coords, 0);
	if (spawn_enemy_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	if (spawn_coin_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	game->player = player;
	return (SUCCESS);
}
