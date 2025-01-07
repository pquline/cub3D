/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/07 15:07:28 by lfarhi           ###   ########.fr       */
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
				coin = spawn_entity(game, &orbe_update, &orbe_minimap, game->assets.coin[0]);
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

static float	get_distance(size_t x, size_t y, t_vector2 v)
{
	float	dx;
	float	dy;

	dx = (float)x - (float)v.x;
	dy = (float)y - (float)v.y;
	return (sqrtf(dx * dx + dy * dy));
}

static t_vector2	get_farthest_tile(t_map *map)
{
	size_t		x;
	size_t		y;
	t_vector2	tile;
	float		current;
	float		max;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			current = get_distance(x, y, map->start_coords);
			if (current > max && map->visited[y][x] == TRUE)
			{
				tile.x = x;
				tile.y = y;
				max = current;
			}
			++x;
		}
		++y;
	}
	return (tile);
}

static t_bool	spawn_enemy_entities(t_game *game, t_map *map)
{
	size_t		index;
	t_entity	*enemy;
	t_vector2	pos;

	pos = get_farthest_tile(map);
	index = 0;
	while (index < 4)
	{
		enemy = spawn_entity(game, &ghost_update, &ghost_minimap, game->assets.enemy[index][0]);
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
