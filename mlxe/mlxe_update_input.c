/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_update_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:44:15 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/15 19:10:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_update_input(t_window *window)
{
	int	i;

	i = 0;
	mlx_mouse_get_pos(window->mlx, window->win,
		&window->mouse.x, &window->mouse.y);
	while (i < MAX_ALL_KEYS)
	{
		if ((window->keys[i] & 0xF) == STATE_ONDOWN)
			window->keys[i] = (window->keys[i] << 4) + STATE_ONPRESSED;
		else if ((window->keys[i] & 0xF) == STATE_ONRELEASE)
			window->keys[i] = (window->keys[i] << 4);
		i++;
	}
}

t_bool	mlxe_is_key_down(t_window *window, int keysym)
{
	return ((window->keys[keysym] & 0xF) == STATE_ONDOWN);
}

t_bool	mlxe_is_key_pressed(t_window *window, int keysym)
{
	return ((window->keys[keysym] & 0xF) == STATE_ONPRESSED);
}

t_bool	mlxe_is_key_released(t_window *window, int keysym)
{
	return ((window->keys[keysym] & 0xF) == STATE_ONRELEASE);
}
