/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:34:02 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 23:34:02 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

static int	mlxe_loop_(t_window *window)
{
	if (window->running)
		window->funct_ptr(window, window->data);
	else
		mlx_loop_end(window->mlx);
	return (0);
}

void	mlxe_loop(t_window *window,
	void (*funct_ptr)(t_window *, void *data), void *data)
{
	window->data = data;
	window->funct_ptr = funct_ptr;
	window->running = TRUE;
	mlx_loop_hook(window->mlx, mlxe_loop_, window);
	mlx_loop(window->mlx);
}
