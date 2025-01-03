/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:12:10 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/03 12:02:22 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static void	change_bounds(t_window *window,
	t_coords *coords, t_texture *texture)
{
	if (coords->src.x + coords->src.width > texture->size.x)
		coords->src.width = texture->size.x - coords->src.x;
	if (coords->src.y + coords->src.height > texture->size.y)
		coords->src.height = texture->size.y - coords->src.y;
	if (coords->dest.x + coords->dest.width > window->buffer->size.x)
		coords->dest.width = window->buffer->size.x - coords->dest.x;
	if (coords->dest.y + coords->dest.height > window->buffer->size.y)
		coords->dest.height = window->buffer->size.y - coords->dest.y;
}

static void	draw_subtexture_size_angle(t_window *window,
			t_texture *texture, t_coords coords, float angle)
{
	float		x_ratio;
	float		y_ratio;
	t_vector2	inc;
	t_color		texture_color;

	x_ratio = (float)coords.src.width / (float)coords.dest.width;
	y_ratio = (float)coords.src.height / (float)coords.dest.height;
	change_bounds(window, &coords, texture);
	inc.y = 0;
	while (inc.y < coords.dest.height)
	{
		inc.x = 0;
		while (inc.x < coords.dest.width)
		{
			texture_color = mlxe_read_pixel(texture, coords.src.x
					+ (inc.x * x_ratio), coords.src.y + (inc.y * y_ratio));
			if (!(texture_color & 0xFF000000))
			{
				//t_vector2	pos = {coords.dest.x + inc.x, coords.dest.y + inc.y};
				//rotate
				t_vector2	new_pos = {coords.dest.x + (inc.x - coords.dest.width / 2) * cos(angle) - (inc.y - coords.dest.height / 2) * sin(angle),
					coords.dest.y + (inc.x - coords.dest.width / 2) * sin(angle) + (inc.y - coords.dest.height / 2) * cos(angle)};
				mlxe_write_pixel(window->buffer, new_pos.x,
					new_pos.y, texture_color);
			}
			inc.x++;
		}
		inc.y++;
	}
}

void	check_door(t_entity *entity, t_game *game)
{
	if (mlxe_is_key_down(game->window, XK_space) || mlxe_is_key_down(game->window, MOUSE_LEFT))
	{
		t_ray ray = raycast(&game->engine, entity->dir);
		if (ray.dist > 2)
			return ;
		if (ray.tile_id == DOOR_HOR || ray.tile_id == DOOR_VER)
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

	draw_subtexture_size_angle(game->window,
		game->assets.map_player[0]->texture,
		(t_coords){game->assets.map_player[(int)entity->anim_map]->rect, (t_rect){50, 50, 10, 10}}, entity->dir);
	mlxe_draw_rect(game->window, (t_rect){0, 0, 100, 100}, mlxe_color(14*4,5*4,58*4));
	mlxe_draw_rect(game->window, (t_rect){1, 1, 100, 100}, mlxe_color(14*4,5*4,58*4));
	entity->anim_map += 0.05;
	if (entity->anim_map >= 6)
		entity->anim_map = 0;
}
