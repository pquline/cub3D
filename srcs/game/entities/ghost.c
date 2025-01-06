/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/06 13:36:14 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void ghost_update(t_entity *entity)
{
	(void)entity;

}
void ghost_minimap(t_entity *entity)
{
	t_camera *camera;
	int monster_id = 0;

	camera = &entity->game->engine.camera;
	t_coords coords = (t_coords){entity->game->assets.map_enemy[monster_id]->rect,
	(t_rect){((entity->pos[0] - camera->x + 5) *10) - 8,
	((entity->pos[1] - camera->y + 5) *10) - 8,
	16, 16}};
	coords = mask_minimap(coords);
	mlxe_draw_subtexture_size(entity->game->window, entity->game->assets.map_enemy[monster_id]->texture, coords, mlxe_color(255, 255, 255));
}
