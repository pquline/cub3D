/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_subtexture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:41:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:41:01 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static void	change_bounds(t_window *window,
	t_vector2 *pos, t_rect *rect, t_texture *texture)
{
	if (pos->x < 0)
	{
		rect->width += pos->x;
		rect->x -= pos->x;
		pos->x = 0;
	}
	if (pos->y < 0)
	{
		rect->height += pos->y;
		rect->y -= pos->y;
		pos->y = 0;
	}
	if (rect->x + rect->width > texture->size.x)
		rect->width = texture->size.x - rect->x;
	if (rect->y + rect->height > texture->size.y)
		rect->height = texture->size.y - rect->y;
	if (pos->x + rect->width > window->buffer->size.x)
		rect->width = window->buffer->size.x - pos->x;
	if (pos->y + rect->height > window->buffer->size.y)
		rect->height = window->buffer->size.y - pos->y;
}

void	mlxe_draw_subtexture(t_window *window,
	t_texture *texture, t_vector2 pos, t_rect rect)
{
	int				i;
	int				j;
	unsigned int	alpha;
	t_color			color;

	change_bounds(window, &pos, &rect, texture);
	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			color = mlxe_read_pixel(texture, rect.x + j, rect.y + i);
			alpha = color & 0xFF000000;
			if (!alpha)
				mlxe_write_pixel(window->buffer, pos.x + j, pos.y + i, color);
			j++;
		}
		i++;
	}
}
