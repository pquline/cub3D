/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 12:17:41 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static t_bool	tile_is_accessible(t_vector2 next, \
	t_vector2 curr, t_map *map, t_visited visited)
{
	if (next.x < 0 || next.x >= (int)map->width || next.y < 0 \
			|| next.y >= (int)map->height)
		return (FALSE);
	if (visited == VISITED_FALSE)
		return (FALSE);
	if (map->grid[(int)curr.y][(int)next.x].id == WALL)
		return (FALSE);
	if (map->grid[(int)curr.y][(int)next.x].id == DOOR \
			&& !door_is_open(&map->grid[(int)curr.y][(int)next.x]))
		return (FALSE);
	return (TRUE);
}

static t_vector2	move_horizontally(t_vector2 target, \
	t_vector2 curr, t_map *map)
{
	t_vector2	next;
	const float	dx = target.x - curr.x;
	const float	dy = target.y - curr.y;

	next.x = curr.x + (dx > 0 ? 1 : -1);
	next.y = curr.y;
	if (tile_is_accessible(next, curr, map, \
			map->visited[(int)curr.y][(int)next.x]))
		return (next);
	next.x = curr.x;
	next.y = curr.y + (dy > 0 ? 1 : -1);
	if (tile_is_accessible(next, curr, map, \
			map->visited[(int)next.y][(int)curr.x]))
		return (next);
	return (curr);
}

static t_vector2	move_vertically(t_vector2 target, \
	t_vector2 curr, t_map *map)
{
	t_vector2	next;
	const float	dx = target.x - curr.x;
	const float	dy = target.y - curr.y;

	next.x = curr.x;
	next.y = curr.y + (dy > 0 ? 1 : -1);
	if (tile_is_accessible(next, curr, map, \
			map->visited[(int)next.y][(int)curr.x]))
		return (next);
	next.x = curr.x + (dx > 0 ? 1 : -1);
	next.y = curr.y;
	if (tile_is_accessible(next, curr, map, \
			map->visited[(int)curr.y][(int)next.x]))
		return (next);
	return (curr);
}

t_vector2	find_next_tile(t_vector2 curr, t_vector2 target, \
	t_map *map)
{
	t_vector2	next;
	const float	dx = target.x - curr.x;
	const float	dy = target.y - curr.y;

	if (fabs(dx) >= fabs(dy))
		next = move_horizontally(target, curr, map);
	else
		next = move_vertically(target, curr, map);
	return (next);
}

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 pos, float dir)
{
	t_enemy			*data;
	const t_game	*game = (t_game *)enemy->game;
	t_vector2		temp;

	data = (t_enemy *)enemy->data;
	temp = pos;
	if (player_is_invulnerable((t_game *)game))
		temp = get_farthest_tile(game->engine.map, \
			(t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
	else if (type == ENEMY_PINK)
		temp = (t_vector2){pos.x + 4 * cos(dir), pos.y + 4 * sin(dir)};
	else if (type == ENEMY_CYAN)
		temp = (t_vector2){pos.x + 2 * (pos.x - (int)data->red->pos[0]), \
			pos.y + 2 * (pos.y - (int)data->red->pos[1])};
	else if (type == ENEMY_ORANGE)
		temp = (t_vector2){rand() % game->engine.map->width, \
			rand() % game->engine.map->height};
	temp = (t_vector2){fmax(0, fmin(temp.x, game->engine.map->width - 1)), \
		fmax(0, fmin(temp.y, game->engine.map->height - 1))};
	data->target = find_next_tile((t_vector2){(int)enemy->pos[0], \
		(int)enemy->pos[1]}, temp, game->engine.map);
}

static void	detect_collision(t_entity *enemy)
{
	t_game	*game;
	float	dist;

	game = (t_game *)enemy->game;
	dist = sqrt(pow(enemy->pos[0] - game->player->pos[0], 2) \
		+ pow(enemy->pos[1] - game->player->pos[1], 2));
	if (dist < 0.5)
	{
		if (player_is_invulnerable(game))
		{
			//Respawn Enemy
		}
		else
			game->window->funct_ptr = gameover_loop;
	}
}

void	ghost_update(t_entity *enemy)
{
	t_enemy	*data;
	t_game	*game;
	float	dx;
	float	dy;
	int		sp_idx;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	dx = fabs((data->target.x + 0.5) - enemy->pos[0]);
	dy = fabs((data->target.y + 0.5) - enemy->pos[1]);
	if (dx * dx + dy * dy < ENTITY_SPEED + 0.01)
		get_next_target(enemy, data->type, \
			(t_vector2){(int)game->player->pos[0], \
			(int)game->player->pos[1]}, game->player->mov_dir);
	if (dx > 0.01 && data->target.x + 0.5 < enemy->pos[0])
		add_move(enemy, -ENTITY_SPEED, 0);
	else if (dx > 0.01)
		add_move(enemy, ENTITY_SPEED, 0);
	if (dy > 0.01 && data->target.y + 0.5 < enemy->pos[1])
		add_move(enemy, 0, -ENTITY_SPEED);
	else if (dy > 0.01)
		add_move(enemy, 0, ENTITY_SPEED);
	detect_collision(enemy);
	sp_idx = data->type;
	if (player_is_invulnerable(game))
		sp_idx = 4;
	enemy->sprites = game->assets.enemy[sp_idx][game->current_time.tv_usec \
		/ 200000 % 4];
}

void	ghost_minimap(t_entity *enemy)
{
	t_camera	*camera;
	t_coords	coords;
	t_enemy		*data;
	t_game		*game;
	int			sp_idx;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	camera = &game->engine.camera;
	sp_idx = data->type;
	if (player_is_invulnerable(game))
		sp_idx = 4;
	coords = (t_coords){game->assets.map_enemy[sp_idx]->rect, \
		(t_rect){((enemy->pos[0] - camera->x + 5) *10) - 8, \
		((enemy->pos[1] - camera->y + 5) *10) - 8, 12, 12}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, \
		game->assets.map_enemy[sp_idx], \
		coords);
}
