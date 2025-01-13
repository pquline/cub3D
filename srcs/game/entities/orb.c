/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:52 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 13:36:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	orb_update(t_entity *entity)
{
	t_game		*game;
	t_vector2	orb_pos;
	t_vector2	player_pos;

	game = entity->game;
	orb_pos = (t_vector2){entity->pos[0], entity->pos[1]};
	player_pos = (t_vector2){game->player->pos[0], game->player->pos[1]};
	entity->sprites = game->assets.orb[game->current_time.tv_usec
		/ 200000 % 4];
	if (orb_pos.x == player_pos.x && orb_pos.y == player_pos.y)
	{
		game->remaining_orbs--;
		delete_entity(&game->engine, entity);
	}
}

void	orb_minimap(t_entity *entity)
{
	t_camera	*camera;
	t_game		*game;
	t_coords	coords;

	game = (t_game *)entity->game;
	camera = &game->engine.camera;
	coords = (t_coords){game->assets.map_orb->rect,
		(t_rect){((entity->pos[0] - camera->x + 10) * 10) - 8,
		((entity->pos[1] - camera->y + 10) * 10) - 8,
		16, 16}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, game->assets.map_orb, coords);
}
