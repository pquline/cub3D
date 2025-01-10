/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:54:36 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 15:54:13 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_coords	mask_minimap(t_coords coords)
{
	if (coords.dest.x + coords.dest.width > 200)
	{
		coords.src.width -= (coords.dest.x + coords.dest.width) - 200;
		coords.dest.width -= (coords.dest.x + coords.dest.width) - 200;
	}
	if (coords.dest.y + coords.dest.height > 200)
	{
		coords.src.height -= (coords.dest.y + coords.dest.height) - 200;
		coords.dest.height -= (coords.dest.y + coords.dest.height) - 200;
	}
	return (coords);
}

void	minimap_entities(t_game *game)
{
	t_list		*current;
	t_entity	*entity;

	current = game->engine.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		entity->efunc.minimap(entity);
		current = current->next;
	}
}

static void	draw_minimap_blocks(t_game *game, t_vector2 iter, t_camera *camera)
{
	t_coords	coords;
	t_rect		rect;

	coords = (t_coords){(t_rect){iter.x * 10, iter.y * 10, 10, 10},
		(t_rect){(iter.x - camera->x + 10) * 10,
		(iter.y - camera->y + 10) * 10, 10, 10}};
	rect = mask_minimap(coords).dest;
	if (game->engine.map->grid[iter.y][iter.x].id == WALL)
		mlxe_draw_fillrect(game->window, rect, mlxe_color(0, 0, 255));
	if (game->engine.map->grid[iter.y][iter.x].id == DOOR)
	{
		if (door_is_open(&game->engine.map->grid[iter.y][iter.x]))
			mlxe_draw_fillrect(game->window, rect, mlxe_color(0, 255, 0));
		else
			mlxe_draw_fillrect(game->window, rect, mlxe_color(255, 0, 255));
	}

}

void	draw_minimap(t_game *game)
{
	t_vector2	iter;
	t_camera	*camera;

	camera = &game->engine.camera;
	iter.y = 0;
	while (iter.y < (int)game->engine.map->height)
	{
		iter.x = 0;
		while (iter.x < (int)game->engine.map->width)
		{
			draw_minimap_blocks(game, iter, camera);
			iter.x++;
		}
		iter.y++;
	}
	minimap_entities(game);
	mlxe_draw_rect(game->window, (t_rect){0, 0, 200, 200},
		mlxe_color(14 * 4, 5 * 4, 58 * 4));
	mlxe_draw_rect(game->window, (t_rect){1, 1, 200, 200},
		mlxe_color(14 * 4, 5 * 4, 58 * 4));
}
