/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:06:36 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 19:07:41 by pfischof         ###   ########.fr       */
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

void	get_next_target(t_entity *enemy, t_enemy_type type, t_vector2 pos)
{
	t_enemy		*data;
	t_game		*game;
	t_vector2	temp;

	data = (t_enemy *)enemy->data;
	game = (t_game *)enemy->game;
	temp = pos;
	if (player_is_invulnerable((t_game *)game))
		temp = get_farthest_tile(game->engine.map, \
			(t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
	else if (type == ENEMY_PINK)
		temp = get_ambush_tile(game, game->player->mov_dir);
	else if (type == ENEMY_CYAN)
		temp = get_ambush_tile(game, game->player->mov_dir + M_PI);
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

void	detect_collision(t_entity *enemy)
{
	float		dist;
	t_game		*game;
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

void	sp_add_move(t_entity *entity, float x, float y, t_vector2 target)
{
	float	t[2];

	t[0] = (float)target.x + 0.5;
	t[1] = (float)target.y + 0.5;
	if (fabs(entity->pos[0] - t[0]) < ENEMY_SPEED * 1.75)
	{
		want_to_move(entity, t[0], 0);
		x = 0;
	}
	if (fabs(entity->pos[1] - t[1]) < ENEMY_SPEED * 1.75)
	{
		want_to_move(entity, 0, t[1]);
		y = 0;
	}
	add_move(entity, x, y);
}
