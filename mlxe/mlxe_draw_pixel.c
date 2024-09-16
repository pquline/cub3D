/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:43:19 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:27:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_draw_pixel(t_texture *texture, int x, int y, t_color color)
{
	if (x < 0 || y < 0 || x >= texture->size.x || y >= texture->size.y)
		return ;
	mlxe_write_pixel(texture, x, y, color);
}
