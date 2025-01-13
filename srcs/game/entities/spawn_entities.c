/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/13 17:16:43 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

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

static t_bool	spawn_orb_entities(t_game *game, t_map *map)
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

static t_bool	spawn_enemy_entities(t_game *game, t_map *map)
{
	int				index;
	t_entity		*red;
	t_entity		*enemy;
	const t_vector2	pos = get_farthest_tile(map, map->start_coords);

	index = 0;
	while (index < 4)
	{
		enemy = ghost_spawn(game, pos, index);
		if (index == ENEMY_RED)
			red = enemy;
		else
			((t_enemy *)enemy->data)->red = red;
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
