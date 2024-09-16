/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:21:36 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/16 15:40:20 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_render(t_window *window)
{
	mlxe_update_input(window);
	mlx_clear_window(window->mlx, window->win);
	mlx_put_image_to_window(window->mlx,
		window->win, window->buffer->img, 0, 0);
	mlx_do_sync(window->mlx);
}
