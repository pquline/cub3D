/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_init_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:22:29 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 18:29:13 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"
#include "mlxe_hooks.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	handle_close(t_window *data)
{
	mlxe_loop_end(data);
	return (0);
}

static int	handle_mousedown(int button, int x, int y, t_window *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	handle_keydown(MAX_KEYS + button, data);
	return (0);
}

static int	handle_mouseup(int button, int x, int y, t_window *data)
{
	data->mouse.x = x;
	data->mouse.y = y;
	handle_keyrelease(MAX_KEYS + button, data);
	return (0);
}

void	mlxe_init_hook(t_window *window)
{
	init_keys(window);
	mlx_hook(window->win, 17, 0, &handle_close, window);
	mlx_mouse_hook(window->win, &handle_mousedown, window);
	mlx_hook(window->win, ButtonRelease,
		ButtonReleaseMask, &handle_mouseup, window);
}
