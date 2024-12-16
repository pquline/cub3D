/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:54:36 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 18:37:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_coords mask_minimap(t_coords coords)
{
	//tronquer les coordonnées si elles dépassent 0,0 -> 100,100
	/*if (coords.dest.x < 0)
	{
		coords.src.x -= coords.dest.x;
		coords.src.width += coords.dest.x;
		coords.dest.x = 0;
	}
	if (coords.dest.y < 0)
	{
		coords.src.y -= coords.dest.y;
		coords.src.height += coords.dest.y;
		coords.dest.y = 0;
	}*/
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
		entity->minimap(entity);
		current = current->next;
	}
}

/*void draw_minimap(t_game *game)
{
	size_t		y;
	size_t		x;
	t_camera	*camera;
	t_coords	coords;

	camera = &game->engine.camera;
	y = 0;
	while (y < game->engine.map->height)
	{
		x = 0;
		while (x < game->engine.map->width)
		{
			coords = mask_minimap((t_coords){(t_rect){(x * 10) - (camera->x * 10) + 50,(y * 10) - (camera->y * 10) + 50, 10, 10},
				(t_rect){x * 10, y * 10, 10, 10}});
			if (game->engine.map->grid[y][x].id == WALL)
				mlxe_draw_fillrect(game->window, coords.dest, mlxe_color(0, 0, 255));
			else if (game->engine.map->grid[y][x].id == DOOR)
				mlxe_draw_fillrect(game->window, coords.dest, mlxe_color(0, 255, 0));
			x++;
		}
		y++;
	}
	//mlxe_draw_fillrect(game->window, (t_rect){(camera->x * 10) - 2, (camera->y * 10) - 2, 4, 4}, mlxe_color(255, 0, 0));
	//mlxe_draw_line(game->window, (t_vector2){camera->x * 10, camera->y * 10}, (t_vector2){camera->x * 10 + 10 * cos(camera->dir), camera->y * 10 + 10 * sin(camera->dir)}, mlxe_color(255, 0, 0));
	//mlxe_draw_sprite(game->window, game->assets.player[0], camera->x * 10, camera->y * 10);
	draw_subtexture_size_angle(game->window,
		game->assets.player[0]->texture,
		(t_coords){game->assets.player[(int)game->assets.player_anim]->rect, (t_rect){camera->x * 10, camera->y * 10, 10, 10}}, camera->dir);
	game->assets.player_anim += 0.05;
	if (game->assets.player_anim >= 6)
		game->assets.player_anim = 0;
}*/

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
			iter.x++;
		}
		iter.y++;
	}
	minimap_entities(game);
}
