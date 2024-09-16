/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:51:46 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 16:00:22 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"
#include "mlxe_hooks.h"

void	init_keys(t_window *window)
{
	int	i;

	i = 0;
	while (i < MAX_ALL_KEYS)
		window->keys[i++] = 0;
	mlx_do_key_autorepeatoff(window->mlx);
	window->mouse = (t_vector2){0, 0};
	mlx_hook(window->win, KeyPress, KeyPressMask, &handle_keydown, window);
	mlx_hook(window->win, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, window);
}

int	handle_keydown(int keysym, t_window *data)
{
	if (keysym == XK_Escape)
		mlxe_loop_end(data);
	data->keys[keysym] = (data->keys[keysym] << 4) + STATE_ONDOWN;
	data->keys[keysym] &= 0xFFFF;
	return (0);
}

int	handle_keyrelease(int keysym, t_window *data)
{
	data->keys[keysym] = (data->keys[keysym] << 4) + STATE_ONRELEASE;
	return (0);
}
