/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:38:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:38:50 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

void	mlxe_draw_texture(t_window *window, t_texture *texture, int x, int y)
{
	mlxe_draw_subtexture(window, texture, (t_vector2){x, y},
		(t_rect){0, 0, texture->size.x, texture->size.y});
}
