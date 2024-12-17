/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:44:28 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 18:00:42 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_ltxt	render_wall(t_engine *engine, t_ray ray)
{
	t_game	*game;
	t_ltxt		res;

	game = (t_game *)engine->game;
	res.texture = game->assets.walls[ray.side_hit];
	res.x = (int)(ray.x_t * res.texture->size.x);
	return (res);
}
