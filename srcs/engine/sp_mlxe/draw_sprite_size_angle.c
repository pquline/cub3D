/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_size_angle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:00:26 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
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

static t_vector2	new_pos(t_coords coords, float angle, t_vector2 inc)
{
	t_vector2	np;

	np = (t_vector2){coords.dest.x + (inc.x - coords.dest.width / 2)
		* cos(angle) - (inc.y - coords.dest.height / 2) * sin(angle),
		coords.dest.y + (inc.x - coords.dest.width / 2) * sin(angle)
		+ (inc.y - coords.dest.height / 2) * cos(angle)};
	return (np);
}

void	draw_sprite_size_angle(t_window *window,
	t_sprite *sprite, t_coords coords, float angle)
{
	float		ratio[2];
	t_vector2	np;
	t_vector2	inc;
	t_color		texture_color;

	ratio[0] = (float)coords.src.width / (float)coords.dest.width;
	ratio[1] = (float)coords.src.height / (float)coords.dest.height;
	change_bounds(window, &coords, sprite->texture);
	inc.y = 0;
	while (inc.y < coords.dest.height)
	{
		inc.x = 0;
		while (inc.x < coords.dest.width)
		{
			texture_color = mlxe_read_pixel(sprite->texture, coords.src.x
					+ (inc.x * ratio[0]), coords.src.y + (inc.y * ratio[1]));
			if (!(texture_color & 0xFF000000))
			{
				np = new_pos(coords, angle, inc);
				mlxe_write_pixel(window->buffer, np.x, np.y, texture_color);
			}
			inc.x++;
		}
		inc.y++;
	}
}
