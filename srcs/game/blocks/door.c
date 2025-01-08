/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 14:45:47 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	render_behind(t_engine *engine, t_rendering *r, t_tile *tile)
{
	t_tile_id	old;

	old = tile->id;
	tile->id = EMPTY;
	r->ray_calc = raycast(engine, r->ray_angle);
	render_line(engine, r);
	tile->id = old;
}

t_ltxt	render_door(t_engine *engine, t_rendering *r)
{
	t_tile		*tile;
	t_game		*game;
	t_ltxt		res;
	t_sprite	*door;
	float		opening;

	game = (t_game *)engine->game;
	door = game->assets.door[game->current_time.tv_usec / 200000 % 4];
	res.texture = door->texture;
	tile = &engine->map->grid[(int)r->ray_calc.ray.y][(int)r->ray_calc.ray.x];
	opening = fabs(tile->data / 100.0);
	res.x = (r->ray_calc.ray.x_t * door->rect.width);
	if (r->ray_calc.ray.x_t < 0.5)
	{
		res.x += ((opening * door->rect.width) / 2);
		if (res.x >= door->rect.width/2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	else
	{
		res.x -= ((opening * door->rect.width) / 2);
		if (res.x < door->rect.width/2)
		{
			render_behind(engine, r, tile);
			res.texture = NULL;
		}
	}
	res.x += door->rect.x;
	return (res);
}
