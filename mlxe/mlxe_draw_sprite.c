/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:37:19 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:37:19 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

void	mlxe_draw_sprite(t_window *window, t_sprite *sprite, int x, int y)
{
	mlxe_draw_subtexture(window, sprite->texture,
		(t_vector2){x + sprite->offset.x, y + sprite->offset.y}, sprite->rect);
}
