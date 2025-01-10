/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 13:16:31 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 pos, float dir)
{
	t_enemy		*data;
	t_game		*game;
	t_vector2	temp;

	data = (t_enemy *)enemy->data;
	game  = (t_game *)enemy->game;
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
	if (dist < 0.6)
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
