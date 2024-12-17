/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:38 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 18:28:46 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"
#include "mlxe_hooks.h"

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

void	mlxe_init_hook(t_window *window);

t_window	*mlxe_init(int width, int height, char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->width = width;
	window->height = height;
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
	mlxe_init_hook(window);
	return (window);
}

t_window	*mlxe_init_fullscreen(char *title)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init();
	mlx_get_screen_size(window->mlx, &window->width, &window->height);
	if (!window->mlx)
		return (exit_free_(window, window->mlx, NULL, NULL));
	window->win = mlx_new_window(window->mlx,
			window->width, window->height, title);
	if (!window->win)
		return (exit_free_(window, window->mlx, window->win, NULL));
	window->buffer = mlxe_create_texture(window,
			window->width, window->height, FALSE);
	if (!window->buffer)
		return (exit_free_(window, window->mlx, window->win, window->buffer));
	window->garbage = NULL;
	window->running = FALSE;
	window->error = MLXE_ERROR_NONE;
	mlxe_init_hook(window);
	return (window);
}
