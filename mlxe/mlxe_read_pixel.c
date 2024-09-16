/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_read_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:26:37 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:26:37 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

t_color	mlxe_read_pixel(t_texture *texture, int x, int y)
{
	int		color;
	char	*dst;

	dst = texture->addr + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return ((t_color){color});
}
