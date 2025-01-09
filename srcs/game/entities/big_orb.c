/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_orb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:52 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/09 16:37:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	big_orb_update(t_entity *entity)
{
	t_game		*game;
	t_vector2	orb_pos;
	t_vector2	player_pos;

	game = entity->game;
	orb_pos = (t_vector2){entity->pos[0], entity->pos[1]};
	player_pos = (t_vector2){game->player->pos[0], game->player->pos[1]};
	if (orb_pos.x == player_pos.x && orb_pos.y == player_pos.y)
	{
		game->remaning_orbs--;
		delete_entity(&game->engine, entity);
		game->invulanerability_time = get_time();
	}
	entity->sprites = game->assets.big_orb[game->current_time.tv_usec \
		/ 200000 % 4];
}

void	big_orb_minimap(t_entity *entity)
{
	t_camera	*camera;
	t_coords	coords;
	t_game		*game;

	game = (t_game *)entity->game;
	camera = &game->engine.camera;
	coords = (t_coords){game->assets.map_big_orb->rect,
		(t_rect){((entity->pos[0] - camera->x + 5) * 10) - 4,
		((entity->pos[1] - camera->y + 5) * 10) - 4,
		8, 8}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, game->assets.map_big_orb, coords);
}
