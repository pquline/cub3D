/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:52 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 11:38:26 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void orbe_update(t_entity *entity)
{
	(void)entity;

}
void orbe_minimap(t_entity *entity)
{
	t_camera *camera;
	t_game *game;

	game = (t_game *)entity->game;
	camera = &game->engine.camera;
	t_coords coords = (t_coords){game->assets.map_coin->rect,
	(t_rect){((entity->pos[0] - camera->x + 5) *10) - 8,
	((entity->pos[1] - camera->y + 5) *10) - 8,
	16, 16}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, game->assets.map_coin, coords);
}
