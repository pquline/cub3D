/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_fillrect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:53:31 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:53:31 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static void	change_bounds(t_window *window, t_rect *rect)
{
	if (rect->x < 0)
	{
		rect->width += rect->x;
		rect->x = 0;
	}
	if (rect->y < 0)
	{
		rect->height += rect->y;
		rect->y = 0;
	}
	if (rect->x + rect->width > window->buffer->size.x)
		rect->width = window->buffer->size.x - rect->x;
	if (rect->y + rect->height > window->buffer->size.y)
		rect->height = window->buffer->size.y - rect->y;
}

void	mlxe_draw_fillrect(t_window *window, t_rect rect, t_color color)
{
	int		i;
	int		j;

	change_bounds(window, &rect);
	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			mlxe_write_pixel(window->buffer, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}
