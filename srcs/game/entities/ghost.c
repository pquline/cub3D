/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 17:06:54 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

t_vector2	find_next_tile(t_vector2 current_pos, t_vector2 target_pos, \
	t_map *map)
{
	t_vector2	next_pos;
	const float	dx = target_pos.x - current_pos.x;
	const float	dy = target_pos.y - current_pos.y;

	next_pos = current_pos;
	if (fabs(dx) >= fabs(dy))
	{
		next_pos.x = current_pos.x + (dx > 0 ? 1 : -1);
		if (next_pos.x >= 0 && next_pos.x < (int)map->width &&
			map->grid[(int)current_pos.y][(int)next_pos.x].id != WALL)
		{
			next_pos.y = current_pos.y;
			return (next_pos);
		}
		next_pos.x = current_pos.x;
		next_pos.y = current_pos.y + (dy > 0 ? 1 : -1);
		if (next_pos.y >= 0 && next_pos.y < (int)map->height &&
				map->grid[(int)next_pos.y][(int)current_pos.x].id != WALL)
			return (next_pos);
	}
	else
	{
		next_pos.y = current_pos.y + (dy > 0 ? 1 : -1);
		if (next_pos.y >= 0 && next_pos.y < (int)map->height &&
			map->grid[(int)next_pos.y][(int)current_pos.x].id != WALL)
		{
			next_pos.x = current_pos.x;
			return (next_pos);
		}
		next_pos.y = current_pos.y;
		next_pos.x = current_pos.x + (dx > 0 ? 1 : -1);
		if (next_pos.x >= 0 && next_pos.x < (int)map->width &&
				map->grid[(int)current_pos.y][(int)next_pos.x].id != WALL)
			return (next_pos);
	}
	return (current_pos);
}

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 player_pos, float player_dir)
{
	t_enemy		*data;
	t_game		*game;
	t_vector2	temp;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	temp = player_pos;

	if (type == ENEMY_PINK)
	{
		temp.x = player_pos.x + 4 * cos(player_dir);
		temp.y = player_pos.y + 4 * sin(player_dir);
		temp.x = fmax(0, fmin(temp.x, game->engine.map->width - 1));
		temp.y = fmax(0, fmin(temp.y, game->engine.map->height - 1));
	}
	else if (type == ENEMY_CYAN)
	{
		temp.x = player_pos.x + 2 * (player_pos.x - (int)data->red->pos[0]);
		temp.y = player_pos.y + 2 * (player_pos.y - (int)data->red->pos[1]);
		temp.x = fmax(0, fmin(temp.x, game->engine.map->width - 1));
		temp.y = fmax(0, fmin(temp.y, game->engine.map->height - 1));
	}
	else if (type == ENEMY_ORANGE)
	{
		temp.x = rand() % game->engine.map->width;
		temp.y = rand() % game->engine.map->height;
	}
	data->target = find_next_tile((t_vector2){(int)enemy->pos[0], \
		(int)enemy->pos[1]}, temp, game->engine.map);
}

void	ghost_update(t_entity *enemy)
{
	t_enemy	*data;
	t_game	*game;
	float	dx;
	float	dy;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	dx = fabs((data->target.x + 0.5) - enemy->pos[0]);
	dy = fabs((data->target.y + 0.5) - enemy->pos[1]);
	if (dx * dx + dy * dy < 0.01)
	{
		get_next_target(enemy, data->type,
			(t_vector2){(int)game->player->pos[0],
			(int)game->player->pos[1]}, game->player->mov_dir);
	}
	if (dx > 0.01 && data->target.x + 0.5 < enemy->pos[0])
		add_move(enemy, -ENTITY_SPEED, 0);
	else if (dx > 0.01)
		add_move(enemy, ENTITY_SPEED, 0);
	if (dy > 0.01 && data->target.y + 0.5 < enemy->pos[1])
		add_move(enemy, 0, -ENTITY_SPEED);
	else if (dy > 0.01)
		add_move(enemy, 0, ENTITY_SPEED);
	enemy->sprites = game->assets.enemy[data->type][game->current_time.tv_usec / 200000 % 4];
}

void	ghost_minimap(t_entity *enemy)
{
	t_enemy		*data;
	t_camera	*camera;
	t_coords	coords;
	t_game *game;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	camera = &game->engine.camera;
	coords = (t_coords){game->assets.map_enemy[data->type]->rect, \
				(t_rect){((enemy->pos[0] - camera->x + 5) *10) - 8,
				((enemy->pos[1] - camera->y + 5) *10) - 8, 12, 12}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, \
		game->assets.map_enemy[data->type], \
		coords);
}
