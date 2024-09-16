/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_get_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:57:45 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:57:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

t_color	mlxe_get_pixel(t_texture *texture, int x, int y)
{
	if (x < 0 || y < 0 || x >= texture->size.x || y >= texture->size.y)
		return (0);
	return (mlxe_read_pixel(texture, x, y));
}
