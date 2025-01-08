/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_size_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/07 16:41:11 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sp_mlxe.h>
#include <math.h>

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

void	draw_sprite_size_angle(t_window *window,
			t_sprite *sprite, t_coords coords, float angle)
{
	float		x_ratio;
	float		y_ratio;
	t_vector2	inc;
	t_color		texture_color;

	x_ratio = (float)coords.src.width / (float)coords.dest.width;
	y_ratio = (float)coords.src.height / (float)coords.dest.height;
	change_bounds(window, &coords, sprite->texture);
	inc.y = 0;
	while (inc.y < coords.dest.height)
	{
		inc.x = 0;
		while (inc.x < coords.dest.width)
		{
			texture_color = mlxe_read_pixel(sprite->texture, coords.src.x
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
