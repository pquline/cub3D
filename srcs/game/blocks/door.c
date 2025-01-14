/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/14 12:18:05 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_ltxt	door_texture(t_engine *engine,
	t_rendering *r, t_tile *tile, t_sprite *door)
{
	const float	opening = fabs(tile->data / 100.0);
	t_ltxt		res;

	res.texture = door->texture;
	res.x = (r->ray_calc.ray.x_t * door->rect.width);
	if (r->ray_calc.ray.x_t < 0.5)
	{
		res.x += ((opening * door->rect.width) / 2);
		if (res.x >= door->rect.width / 2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	else
	{
		res.x -= ((opening * door->rect.width) / 2);
		if (res.x < door->rect.width / 2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	res.x += door->rect.x;
	return (res);
}

t_ltxt	render_door(t_engine *engine, t_rendering *r)
{
	t_tile		*tile;
	t_game		*game;
	t_ltxt		res;
	t_sprite	*door;

	game = (t_game *)engine->game;
	door = game->assets.door[game->current_time.tv_usec / 100000 % 4];
	tile = &engine->map->grid[(int)r->ray_calc.ray.y][(int)r->ray_calc.ray.x];
	res = door_texture(engine, r, tile, door);
	return (res);
}

static t_bool	check_entity_collider(t_game *game, float x, float y)
{
	t_list		*current;
	t_entity	*entity;

	current = game->engine.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		if (sqrt(pow(entity->pos[0] - x, 2)
				+ pow(entity->pos[1] - y, 2)) < 0.75)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

void	toggle_door(t_game	*game, int x, int y)
{
	t_tile	*tile;

	tile = &game->engine.map->grid[y][x];
	if (tile->id == DOOR)
	{
		if (tile->data == 100)
		{
			if (!check_entity_collider(game, x + 0.5f, y + 0.5f))
				tile->data = -96;
		}
		else if (tile->data == 0)
		{
			tile->data = 4;
		}
	}
}

t_bool	door_is_open(t_tile *tile)
{
	if (tile->id == DOOR && tile->data > 0)
		return (TRUE);
	return (FALSE);
}
