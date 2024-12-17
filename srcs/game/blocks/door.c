/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:50:49 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 18:15:12 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_ltxt	render_door(t_engine *engine, t_ray ray)
{
	t_game	*game;
	t_ltxt		res;
	t_sprite	*door;

	game = (t_game *)engine->game;
	int idx = game->current_time.tv_usec / 200000 % 4;
	door = game->assets.door[idx];
	res.texture = door->texture;
	res.x = (int)(door->rect.x + (ray.x_t * door->rect.width));
	return (res);
}