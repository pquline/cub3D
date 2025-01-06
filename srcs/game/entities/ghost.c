/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/06 15:57:00 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void ghost_update(t_entity *entity)
{
	if (entity->game->player->pos[0] < entity->pos[0])
		add_move(entity, -ENTITY_SPEED, 0);
	else if (entity->game->player->pos[0] > entity->pos[0])
		add_move(entity, ENTITY_SPEED, 0);
	if (entity->game->player->pos[1] < entity->pos[1])
		add_move(entity, 0, -ENTITY_SPEED);
	else if (entity->game->player->pos[1] > entity->pos[1])
		add_move(entity, 0, ENTITY_SPEED);
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
