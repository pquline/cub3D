/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/09 12:31:09 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static void	get_accessible_tiles(t_map *map, t_vector2 v)
{
	if (map->visited[v.y][v.x] == TRUE || (map->grid[v.y][v.x].id != EMPTY \
			&& map->grid[v.y][v.x].id != DOOR))
		return ;
	map->visited[v.y][v.x] = TRUE;
	get_accessible_tiles(map, (t_vector2){v.x - 1, v.y});
	get_accessible_tiles(map, (t_vector2){v.x + 1, v.y});
	get_accessible_tiles(map, (t_vector2){v.x, v.y - 1});
	get_accessible_tiles(map, (t_vector2){v.x, v.y + 1});
}

static t_bool	init_accessible_map(t_map *map)
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
				coin = spawn_entity(&game->engine, game, (t_efunc){&orbe_update, &orbe_minimap, NULL}, game->assets.coin[0]);
				if (coin == NULL)
					return (FAILURE);
				set_entity_pos(coin, (float)v.x + 0.5, (float)v.y + 0.5);
				game->remaning_orbs++;
			}
			++v.x;
		}
		++v.y;
	}
	return (SUCCESS);
}

static float	get_distance(size_t x, size_t y, t_vector2 v)
{
	const float	dx = (float)x - (float)v.x;
	const float	dy = (float)y - (float)v.y;

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
	max = 0;
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

static t_bool	init_enemy_data(t_entity *enemy, t_enemy_type type)
{
	t_enemy	*ghost;

	ghost = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
	if (ghost == NULL)
		return (FAILURE);
	ghost->type = type;
	ghost->mode = ENEMY_CHASING;
	ghost->red = NULL;
	enemy->data = ghost;
	return (SUCCESS);
}

static t_bool	spawn_enemy_entities(t_game *game, t_map *map)
{
	size_t		index;
	t_enemy		*data;
	t_entity	*enemy;
	t_entity	*red;
	t_vector2	pos;

	pos = get_farthest_tile(map);
	index = 0;
	while (index < 4)
	{
		enemy = spawn_entity(&game->engine, game, (t_efunc){&ghost_update, &ghost_minimap, free}, game->assets.enemy[index][0]);
		if (enemy == NULL)
			return (FAILURE);
		set_entity_pos(enemy, (float)pos.x + 0.5, (float)pos.y + 0.5);
		if (init_enemy_data(enemy, index) == FAILURE)
			return (FAILURE);
		data = (t_enemy *)enemy->data;
		if (index == ENEMY_RED)
			red = enemy;
		else
			data->red = red;
		data->target = (t_vector2){(int)enemy->pos[0], (int)enemy->pos[1]};
		++index;
	}
	return (SUCCESS);
}

t_bool	spawn_entities(t_game *game)
{
	t_entity	*player;

	player = spawn_entity(&game->engine, game, (t_efunc){&player_update, &player_minimap, NULL}, NULL);
	if (player == NULL)
		return (FAILURE);
	if (init_accessible_map(game->engine.map) == FAILURE)
		return (FAILURE);
	get_accessible_tiles(game->engine.map, game->engine.map->start_coords);
	if (spawn_enemy_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	if (spawn_coin_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	game->player = player;
	return (SUCCESS);
}
