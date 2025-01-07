/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/07 17:35:46 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	blue_ghost_move(t_entity *entity)
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

void	pink_ghost_move(t_entity *entity)
{

}

void	orange_ghost_move(t_entity *entity)
{

}

void	red_ghost_move(t_entity *entity)
{

}

void ghost_update(t_entity *entity)
{
	const t_enemy_type	type[4] = {BLUE, PINK, ORANGE, RED};
	void				(*function[4])(t_entity *) = {blue_ghost_move, pink_ghost_move, \
										orange_ghost_move, red_ghost_move};
	size_t				index;
	t_enemy				*enemy;

	enemy = (t_enemy *)entity->data;
	index = 0;
	while (index < 4)
	{
		if (type[index] == enemy->type)
			function[index](entity);
		++index;
	}
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
