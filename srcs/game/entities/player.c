/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:12:10 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 11:26:23 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	check_door(t_entity *entity, t_game *game)
{
	if (mlxe_is_key_down(game->window, XK_space) || mlxe_is_key_down(game->window, MOUSE_LEFT))
	{
		t_ray ray = raycast(&game->engine, entity->dir);
		if (ray.dist > 2)
			return ;
		if (ray.tile_id == DOOR)
		{
			t_tile *tile = &game->engine.map->grid[(int)ray.y][(int)ray.x];
			if (tile->data == 100)
				tile->data = -96;
			else if (tile->data == 0)
				tile->data = 4;
		}
	}
}

void player_update(t_entity *entity)
{
	t_game	*game = entity->game;
	float	speed_move;
	float	speed_mouse;

	speed_move = adaptive_speed(0.003, game->delta_time);
	speed_mouse = adaptive_speed(0.0003, game->delta_time);
	if (mlxe_is_key_pressed(game->window, XK_w))
		add_move(entity, cos(entity->dir) * speed_move, sin(entity->dir) * speed_move);
	if (mlxe_is_key_pressed(game->window, XK_s))
		add_move(entity, -cos(entity->dir) * speed_move, -sin(entity->dir) * speed_move);
	if (mlxe_is_key_pressed(game->window, XK_d))
		add_move(entity, cos(entity->dir + M_PI_2) * speed_move, sin(entity->dir + M_PI_2) * speed_move);
	if (mlxe_is_key_pressed(game->window, XK_a))
		add_move(entity, cos(entity->dir - M_PI_2) * speed_move, sin(entity->dir - M_PI_2) * speed_move);
	entity->dir -= (game->window->width / 2 - game->window->mouse.x) * speed_mouse;
	if (mlxe_is_key_pressed(game->window, XK_Left))
		entity->dir -= speed_move;
	if (mlxe_is_key_pressed(game->window, XK_Right))
		entity->dir += speed_move;
	entity->game->engine.camera.x = entity->pos[0];
	entity->game->engine.camera.y = entity->pos[1];
	entity->game->engine.camera.dir = entity->dir;
	check_door(entity, game);
}
void player_minimap(t_entity *entity)
{
	t_game	*game = entity->game;

	draw_sprite_size_angle(game->window,
		game->assets.map_player[0],
		(t_coords){game->assets.map_player[(int)entity->anim_map]->rect, (t_rect){50, 50, 10, 10}}, entity->dir);
	entity->anim_map += 0.05;
	if (entity->anim_map >= 6)
		entity->anim_map = 0;
}
