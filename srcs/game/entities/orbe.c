/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:52 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/07 16:38:16 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <sp_mlxe.h>

void orbe_update(t_entity *entity)
{
	(void)entity;

}
void orbe_minimap(t_entity *entity)
{
	t_camera *camera;

	camera = &entity->game->engine.camera;
	t_coords coords = (t_coords){entity->game->assets.map_coin->rect,
	(t_rect){((entity->pos[0] - camera->x + 5) *10) - 8,
	((entity->pos[1] - camera->y + 5) *10) - 8,
	16, 16}};
	coords = mask_minimap(coords);
	draw_sprite_mask(entity->game->window, entity->game->assets.map_coin, coords);
}
