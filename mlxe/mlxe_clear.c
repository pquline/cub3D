/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:13:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/11 16:03:21 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_clear(t_window *window)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->buffer->size.y)
	{
		j = 0;
		while (j < window->buffer->size.x)
		{
			mlxe_write_pixel(window->buffer, j, i, 0);
			j++;
		}
		i++;
	}
}

void	mlxe_clear_color(t_window *window, t_color color)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->buffer->size.y)
	{
		j = 0;
		while (j < window->buffer->size.x)
		{
			mlxe_write_pixel(window->buffer, j, i, color);
			j++;
		}
		i++;
	}
}
