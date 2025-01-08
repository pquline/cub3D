/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:14 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 16:00:51 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_bool	check_collider_block(t_tile *tile)
{
	if (tile->id == EMPTY)
		return (SUCCESS);
	if (tile->id == DOOR && door_is_open(tile))
		return (SUCCESS);
	return (FAILURE);
}

static t_bool	check_box(t_engine *engine, float x, float y)
{
	float		dx;
	float		dy;
	int			check_x;
	int			check_y;
	const float	half_size = 0.05;

	dx = -half_size;
	while (dx <= half_size)
	{
		dy = -half_size;
		while (dy <= half_size)
		{
			check_x = (int)(x + dx);
			check_y = (int)(y + dy);
			if (check_x < 0 || check_x >= (int)engine->map->width
				|| check_y < 0 || check_y >= (int)engine->map->height)
				return (FAILURE);
			if (check_collider_block(
					&engine->map->grid[check_y][check_x]) == FAILURE)
				return (FAILURE);
			dy += half_size;
		}
		dx += half_size;
	}
	return (SUCCESS);
}

t_bool	want_to_move(t_entity *entity, float x, float y)
{
	t_engine	*engine;
	float		mov_dir;
	t_ray		ray;
	float		dist;

	engine = &((t_game *)entity->game)->engine;
	if (x < 0 || x >= engine->map->width || y < 0 || y >= engine->map->height)
		return (FAILURE);
	if (check_collider_block(&engine->map->grid[(int)y][(int)x]) == FAILURE)
		return (FAILURE);
	if (check_box(engine, x, y) == FAILURE)
		return (FAILURE);
	mov_dir = atan2(y - entity->pos[1], x - entity->pos[0]);
	ray = raycast(engine, mov_dir).ray;
	dist = sqrt(pow(entity->pos[0] - x, 2) + pow(entity->pos[1] - y, 2));
	if (ray.hit && ray.dist < dist)
	{
		if (check_collider_block(
				&engine->map->grid[(int)ray.y][(int)ray.x]) == FAILURE)
			return (FAILURE);
	}
	entity->pos[0] = x;
	entity->pos[1] = y;
	entity->mov_dir = mov_dir;
	return (SUCCESS);
}

t_bool	add_move(t_entity *entity, float x, float y)
{
	return (want_to_move(entity, entity->pos[0] + x, entity->pos[1] + y));
}
