/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_rect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:51:26 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:51:26 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

void	mlxe_draw_rect(t_window *window, t_rect rect, t_color color)
{
	mlxe_draw_line(window, (t_vector2){rect.x, rect.y},
		(t_vector2){rect.x + rect.width, rect.y}, color);
	mlxe_draw_line(window, (t_vector2){rect.x + rect.width, rect.y},
		(t_vector2){rect.x + rect.width, rect.y + rect.height}, color);
	mlxe_draw_line(window,
		(t_vector2){rect.x + rect.width, rect.y + rect.height},
		(t_vector2){rect.x, rect.y + rect.height}, color);
	mlxe_draw_line(window, (t_vector2){rect.x, rect.y + rect.height},
		(t_vector2){rect.x, rect.y}, color);
}
