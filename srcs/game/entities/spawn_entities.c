/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:21:36 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/17 22:22:19 by pfischof         ###   ########.fr       */
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

static void	print_visited(t_map *map, t_bool visited[][map->width])
{
	dprintf(2, "\n\n----------------- VISITED\n");
	for (size_t i = 0; i < map->height; ++i)
	{
		for (size_t j = 0; j < map->width; ++j)
			dprintf(2, "%d", visited[i][j] == TRUE ? 0 : 1);
		dprintf(2, "\n");
	}
}

t_bool	spawn_coin_entities(t_map *map)
{
	t_bool	visited[map->height][map->width];
	size_t	count;

	ft_bzero(visited, (map->height * map->width) * sizeof(t_bool));
	count = get_accessible_tiles_count(map, map->start_coords, visited, 0) / 2;
	print_visited(map, visited);
	dprintf(2, "count = %zu\n", count);
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
	enemy[0] = spawn_entity(game, &update_enemy, &draw_minimap_enemy, NULL);
	enemy[1] = spawn_entity(game, &update_enemy, &draw_minimap_enemy, NULL);
	enemy[2] = spawn_entity(game, &update_enemy, &draw_minimap_enemy, NULL);
	enemy[3] = spawn_entity(game, &update_enemy, &draw_minimap_enemy, NULL);
	if (spawn_coin_entities(game->engine.map) == FAILURE)
		return (FAILURE);
	return (player && enemy[0] && enemy[1] && enemy[2] && enemy[3]);
}
