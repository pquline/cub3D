/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_mlxe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:06:15 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/07 16:40:52 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SP_MLXE_H
# define SP_MLXE_H
# include <mlxe.h>

void	draw_subtexture_size_z(t_window *window,
			t_texture *texture, t_coords coords, float *z_buffer, float z);

void	draw_sprite_size_angle(t_window *window,
			t_sprite *sprite, t_coords coords, float angle);

void	draw_sprite_mask(t_window *window, t_sprite *sprite, t_coords coords);

#endif
