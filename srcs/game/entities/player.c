/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:12:10 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 15:54:46 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static void	check_door(t_entity *entity, t_game *game)
{
	t_ray	ray;

	if (mlxe_is_key_down(game->window, XK_space)
		|| mlxe_is_key_down(game->window, MOUSE_LEFT))
	{
		ray = raycast(&game->engine, entity->dir).ray;
		if (ray.hit == FALSE || ray.dist > 2)
			return ;
		if (ray.tile_id == DOOR)
			toggle_door(game, (int)ray.x, (int)ray.y);
	}
}

static void	update_keys(t_entity *entity, float speed_move)
{
	t_game	*game;

	game = entity->game;
	if (mlxe_is_key_pressed(game->window, XK_w))
	{
		add_move(entity, cos(entity->dir) * speed_move, 0);
		add_move(entity, 0, sin(entity->dir) * speed_move);
	}
	if (mlxe_is_key_pressed(game->window, XK_s))
	{
		add_move(entity, -cos(entity->dir) * speed_move, 0);
		add_move(entity, 0, -sin(entity->dir) * speed_move);
	}
	if (mlxe_is_key_pressed(game->window, XK_d))
		add_move(entity, cos(entity->dir + M_PI_2) * speed_move,
			sin(entity->dir + M_PI_2) * speed_move);
	if (mlxe_is_key_pressed(game->window, XK_a))
		add_move(entity, cos(entity->dir - M_PI_2) * speed_move,
			sin(entity->dir - M_PI_2) * speed_move);
}

void	player_update(t_entity *entity)
{
	t_game	*game;
	float	speed_move;
	float	speed_mouse;

	game = entity->game;
	speed_move = adaptive_speed(0.003, game->delta_time);
	speed_mouse = adaptive_speed(0.0003, game->delta_time);
	update_keys(entity, speed_move);
	entity->dir -= (game->window->width / 2
			- game->window->mouse.x) * speed_mouse;
	if (mlxe_is_key_pressed(game->window, XK_Left))
		entity->dir -= speed_move;
	if (mlxe_is_key_pressed(game->window, XK_Right))
		entity->dir += speed_move;
	game->engine.camera.x = entity->pos[0];
	game->engine.camera.y = entity->pos[1];
	game->engine.camera.dir = entity->dir;
	check_door(entity, game);
}

void	player_minimap(t_entity *entity)
{
	t_game	*game;

	game = entity->game;
	draw_sprite_size_angle(game->window,
		game->assets.map_player[0],
		(t_coords){game->assets.map_player[(int)entity->anim_map]->rect,
		(t_rect){100, 100, 10, 10}}, entity->dir);
	entity->anim_map += 0.05;
	if (entity->anim_map >= 6)
		entity->anim_map = 0;
}

t_bool	player_is_invulnerable(t_game *game)
{
	if (game->invulanerability_time.tv_sec
		+ INVULNERABILITY_TIME > game->current_time.tv_sec)
		return (TRUE);
	return (FALSE);
}
