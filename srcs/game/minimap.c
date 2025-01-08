/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:54:36 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 11:47:23 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_coords mask_minimap(t_coords coords)
{
	if (coords.dest.x + coords.dest.width > 100)
	{
		coords.src.width -= (coords.dest.x + coords.dest.width) - 100;
		coords.dest.width -= (coords.dest.x + coords.dest.width) - 100;
	}
	if (coords.dest.y + coords.dest.height > 100)
	{
		coords.src.height -= (coords.dest.y + coords.dest.height) - 100;
		coords.dest.height -= (coords.dest.y + coords.dest.height) - 100;
	}
	return (coords);
}

void	minimap_entities(t_game *game)
{
	t_list	*current;
	t_entity	*entity;

	current = game->engine.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		entity->efunc.minimap(entity);
		current = current->next;
	}
}

void draw_minimap(t_game *game)
{
	t_vector2 iter;
	t_camera *camera;

	camera = &game->engine.camera;
	iter.y = 0;
	while (iter.y < (int)game->engine.map->height)
	{
		iter.x = 0;
		while (iter.x < (int)game->engine.map->width)
		{
			//t_rect rect = {(iter.x - camera->x + 5) *10, (iter.y - camera->y + 5) *10, 10, 10};
			t_coords coords = {(t_rect){iter.x * 10, iter.y * 10, 10, 10},(t_rect){(iter.x - camera->x + 5) *10, (iter.y - camera->y + 5) *10, 10, 10}};
			t_rect rect = mask_minimap(coords).dest;
			if (game->engine.map->grid[iter.y][iter.x].id == WALL)
				mlxe_draw_fillrect(game->window, rect, mlxe_color(0, 0, 255));
			if (game->engine.map->grid[iter.y][iter.x].id == DOOR)
				mlxe_draw_fillrect(game->window, rect, mlxe_color(0, 255, 0));
			iter.x++;
		}
		iter.y++;
	}
	minimap_entities(game);
	mlxe_draw_rect(game->window, (t_rect){0, 0, 100, 100}, mlxe_color(14*4,5*4,58*4));
	mlxe_draw_rect(game->window, (t_rect){1, 1, 100, 100}, mlxe_color(14*4,5*4,58*4));
}
