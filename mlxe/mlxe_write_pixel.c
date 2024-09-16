/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_write_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:26:29 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:26:29 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_write_pixel(t_texture *texture, int x, int y, t_color color)
{
	(void)texture;
	(void)x;
	(void)y;
	(void)color;
	*(unsigned int *)(texture->addr
			+ (y * texture->size_line + x
				* (texture->bits_per_pixel / 8))) = color;
}
