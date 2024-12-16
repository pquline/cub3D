/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:40:19 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 12:50:54 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

int	mlxe_mouse_get_pos(t_window *window, int *x, int *y)
{
	return (mlx_mouse_get_pos(window->mlx, window->win, x, y));
}

int	mlxe_mouse_move(t_window *window, int x, int y)
{
	return (mlx_mouse_move(window->mlx, window->win, x, y));
}
