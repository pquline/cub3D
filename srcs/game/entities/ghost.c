/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 15:55:10 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static t_vector2	get_ambush_tile(t_game *game, float dir)
{
	t_ray_calc	raycalc;

	raycalc = raycast(&game->engine, dir);
	if (raycalc.ray.hit == TRUE)
	{
		if (raycalc.side == 0)
			raycalc.map_x -= raycalc.step_x;
		else
			raycalc.map_y -= raycalc.step_y;
		return ((t_vector2){raycalc.map_x, raycalc.map_y});
	}
	return ((t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
}

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 pos, float dir)
{
	t_enemy		*data;
	t_game		*game;
	t_vector2	temp;

	data = (t_enemy *)enemy->data;
	game  = (t_game *)enemy->game;
	temp = pos;
	(void)dir;
	if (player_is_invulnerable((t_game *)game))
		temp = get_farthest_tile(game->engine.map, \
			(t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
	else if (type == ENEMY_PINK)
		temp = get_ambush_tile(game, game->player->mov_dir);
		//temp = (t_vector2){pos.x + 4 * cos(dir), pos.y + 4 * sin(dir)};
	else if (type == ENEMY_CYAN)
		temp = get_ambush_tile(game, game->player->mov_dir + M_PI);
		//temp = (t_vector2){pos.x + 2 * (pos.x - (int)data->red->pos[0]), \
		//	pos.y + 2 * (pos.y - (int)data->red->pos[1])};
	else if (type == ENEMY_ORANGE)
		temp = (t_vector2){rand() % game->engine.map->width, \
			rand() % game->engine.map->height};
	temp = (t_vector2){fmax(0, fmin(temp.x, game->engine.map->width - 1)), \
		fmax(0, fmin(temp.y, game->engine.map->height - 1))};
	if (game->engine.map->grid[temp.y][temp.x].id != EMPTY)
		temp = pos;
	reset_path(game);
	data->target = move_to(game, (t_vector2){(int)enemy->pos[0], \
		(int)enemy->pos[1]}, temp);
}

static void	detect_collision(t_entity *enemy)
{
	t_game		*game;
	float		dist;
	t_vector2	pos;

	game = (t_game *)enemy->game;
	dist = sqrt(pow(enemy->pos[0] - game->player->pos[0], 2) \
		+ pow(enemy->pos[1] - game->player->pos[1], 2));
	if (dist < 0.75)
	{
		if (player_is_invulnerable(game))
		{
			pos = get_farthest_tile(game->engine.map, \
				(t_vector2){(int)game->player->pos[0], \
				(int)game->player->pos[1]});
			set_entity_pos(enemy, (float)pos.x + 0.5, (float)pos.y + 0.5);
		}
		else
			game->window->funct_ptr = gameover_loop;
	}
}

static void	sp_add_move(t_entity *entity, float x, float y, t_vector2 target)
{
	float t[2];

	t[0] = (float)target.x + 0.5;
	t[1] = (float)target.y + 0.5;
	if (fabs(entity->pos[0] - t[0]) < ENTITY_SPEED * 1.75)
	{
		want_to_move(entity, t[0], 0);
		x = 0;
	}
	if (fabs(entity->pos[1] - t[1]) < ENTITY_SPEED * 1.75)
	{
		want_to_move(entity, 0, t[1]);
		y = 0;
	}
	add_move(entity, x, y);
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
		sp_add_move(enemy, -ENTITY_SPEED, 0, data->target);
	else if (dx > 0.01)
		sp_add_move(enemy, ENTITY_SPEED, 0, data->target);
	if (dy > 0.01 && data->target.y + 0.5 < enemy->pos[1])
		sp_add_move(enemy, 0, -ENTITY_SPEED, data->target);
	else if (dy > 0.01)
		sp_add_move(enemy, 0, ENTITY_SPEED, data->target);
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
		(t_rect){((enemy->pos[0] - camera->x + 10) *10) - 8, \
		((enemy->pos[1] - camera->y + 10) *10) - 8, 12, 12}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, \
		game->assets.map_enemy[sp_idx], \
		coords);
}
