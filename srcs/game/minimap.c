/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:54:36 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 19:09:07 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

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

void	draw_subtexture_size_angle(t_window *window,
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

void draw_minimap(t_game *game)
{
	size_t		y;
	size_t		x;
	t_camera	*camera;

	camera = &game->engine.camera;
	y = 0;
	while (y < game->engine.map->height)
	{
		x = 0;
		while (x < game->engine.map->width)
		{
			if (game->engine.map->grid[y][x].id == WALL)
				mlxe_draw_fillrect(game->window, (t_rect){x * 10, y * 10, 10, 10}, mlxe_color(0, 0, 255));
			x++;
		}
		y++;
	}
	//mlxe_draw_fillrect(game->window, (t_rect){(camera->x * 10) - 2, (camera->y * 10) - 2, 4, 4}, mlxe_color(255, 0, 0));
	//mlxe_draw_line(game->window, (t_vector2){camera->x * 10, camera->y * 10}, (t_vector2){camera->x * 10 + 10 * cos(camera->dir), camera->y * 10 + 10 * sin(camera->dir)}, mlxe_color(255, 0, 0));
	//mlxe_draw_sprite(game->window, game->assets.player[0], camera->x * 10, camera->y * 10);
	draw_subtexture_size_angle(game->window,
		game->assets.player[0]->texture,
		(t_coords){game->assets.player[(int)game->assets.player_anim]->rect, (t_rect){camera->x * 10, camera->y * 10, 10, 10}}, camera->dir);
	game->assets.player_anim += 0.05;
	if (game->assets.player_anim >= 6)
		game->assets.player_anim = 0;
}
