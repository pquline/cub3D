/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 15:46:16 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static void	get_accessible_tiles(t_map *map, t_vector2 v)
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

static t_bool	init_accessible_map(t_map *map)
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

t_bool	spawn_orb_entity(t_game *game, t_map *map, t_vector2 v)
{
	t_entity	*orb;

	if (big_orb_can_spawn(map, (t_vector2){v.x - BIG_ORBS_DIST, \
		v.y - BIG_ORBS_DIST}, (t_vector2){v.x + BIG_ORBS_DIST, \
		v.y + BIG_ORBS_DIST}))
	{
		orb = spawn_entity(&game->engine, game, (t_efunc){&big_orb_update, \
			&big_orb_minimap, NULL}, game->assets.big_orb[0]);
		map->visited[v.y][v.x] = VISITED_BIG_ORB;
	}
	else
		orb = spawn_entity(&game->engine, game, (t_efunc){&orb_update, \
			&orb_minimap, NULL}, game->assets.orb[0]);
	if (orb == NULL)
		return (FAILURE);
	set_entity_pos(orb, (float)v.x + 0.5, (float)v.y + 0.5);
	return (SUCCESS);
}

t_bool	spawn_orb_entities(t_game *game, t_map *map)
{
	t_vector2	v;

	v.y = 0;
	while ((size_t)v.y < map->height)
	{
		v.x = 0;
		while ((size_t)v.x < map->width)
		{
			if (map->visited[v.y][v.x] == VISITED_TRUE \
				&& !(v.x == map->start_coords.x && v.y == map->start_coords.y) \
				&& map->grid[v.y][v.x].id != DOOR)
			{
				map->visited[v.y][v.x] = VISITED_ORB;
				if (spawn_orb_entity(game, map, v) == FAILURE)
					return (FAILURE);
				game->remaining_orbs++;
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
	size_t			index;
	t_enemy			*data;
	t_entity		*enemy;
	t_entity		*red;
	const t_vector2	pos = get_farthest_tile(map, map->start_coords);

	index = 0;
	while (index < 4)
	{
		enemy = spawn_entity(&game->engine, game, (t_efunc){&ghost_update, \
			&ghost_minimap, free}, game->assets.enemy[index][0]);
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

	player = spawn_entity(&game->engine, game, (t_efunc){&player_update, \
		&player_minimap, NULL}, NULL);
	if (player == NULL)
		return (FAILURE);
	if (init_accessible_map(game->engine.map) == FAILURE)
		return (FAILURE);
	get_accessible_tiles(game->engine.map, game->engine.map->start_coords);
	if (spawn_enemy_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	if (spawn_orb_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	game->player = player;
	return (SUCCESS);
}
