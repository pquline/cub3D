/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/06 14:44:18 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static size_t	get_accessible_tiles_count(t_map *map, t_vector2 v, \
	t_bool visited[][map->width], size_t count)
{
	if (visited[v.y][v.x] == TRUE || map->grid[v.y][v.x].id != EMPTY)
		return (0);
	visited[v.y][v.x] = TRUE;
	return (get_accessible_tiles_count(map, (t_vector2){v.x - 1, v.y}, visited,\
		count) + get_accessible_tiles_count(map, (t_vector2){v.x + 1, v.y}, \
		visited, count) + get_accessible_tiles_count(map, \
		(t_vector2){v.x, v.y - 1}, visited, count) \
		+ get_accessible_tiles_count(map, (t_vector2){v.x, v.y + 1}, visited, \
		count) + 1);
}

t_bool	spawn_coin_entities(t_game *game, t_map *map)
{
	size_t		count;
	t_entity	*coin;
	t_bool		visited[map->height][map->width];
	t_vector2	pos;

	ft_bzero(visited, (map->height * map->width) * sizeof(t_bool));
	count = get_accessible_tiles_count(map, map->start_coords, visited, 0);
	pos.y = 0;
	while ((size_t)pos.y < map->height)
	{
		pos.x = 0;
		while ((size_t)pos.x < map->width)
		{
			if (visited[pos.y][pos.x] == TRUE && !(pos.x == map->start_coords.x \
				&& pos.y == map->start_coords.y))
			{
				coin = spawn_entity(game, &orbe_update, &orbe_minimap, NULL);
				if (coin == NULL)
					return (FAILURE);
				set_entity_pos(coin, (float)pos.x + 0.5, (float)pos.y + 0.5);
			}
			++pos.x;
		}
		++pos.y;
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

t_bool	spawn_entities(t_game *game)
{
	t_entity	*player;
	t_entity	*enemy[4];

	player = spawn_entity(game, &player_update, &player_minimap, NULL);
	enemy[0] = spawn_entity(game, &ghost_update, &ghost_minimap, NULL);
	enemy[1] = spawn_entity(game, &ghost_update, &ghost_minimap, NULL);
	enemy[2] = spawn_entity(game, &ghost_update, &ghost_minimap, NULL);
	enemy[3] = spawn_entity(game, &ghost_update, &ghost_minimap, NULL);
	if (spawn_coin_entities(game, game->engine.map) == FAILURE)
		return (FAILURE);
	if (!(player && enemy[0] && enemy[1] && enemy[2] && enemy[3]))
		return (FAILURE);
	game->player = player;
	return (SUCCESS);
}
