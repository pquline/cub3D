/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:38 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 16:00:25 by lfarhi           ###   ########.fr       */
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

static void	*exit_free_(t_window *window, void *mlx, void *win, void *buffer)
{
	if (buffer)
		mlxe_free_texture(window, buffer);
	if (win)
		mlx_destroy_window(mlx, win);
	if (mlx)
		mlx_destroy_display(mlx);
	if (window)
		free(window);
	return (NULL);
}

t_window	*mlxe_init(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init();
	if (!window->mlx)
		return (exit_free_(window, window->mlx, NULL, NULL));
	window->win = mlx_new_window(window->mlx, width, height, title);
	if (!window->win)
		return (exit_free_(window, window->mlx, window->win, NULL));
	window->buffer = mlxe_create_texture(window, width, height, FALSE);
	if (!window->buffer)
		return (exit_free_(window, window->mlx, window->win, window->buffer));
	window->garbage = NULL;
	window->running = FALSE;
	window->error = MLXE_ERROR_NONE;
	init_keys(window);
	mlx_hook(window->win, 17, 0, &handle_close, window);
	mlx_mouse_hook(window->win, &handle_mousedown, window);
	mlx_hook(window->win, ButtonRelease,
		ButtonReleaseMask, &handle_mouseup, window);
	return (window);
}
