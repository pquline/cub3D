/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:37:47 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/15 22:27:35 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <libft.h>
# include <mlxe.h>
# include "parsing.h"

# include <sys/time.h>
# include <math.h>

typedef struct s_ray
{
	float		x;
	float		y;
	float		dir;
	float		dist;
	float		x_t;
	int			side_hit;
}				t_ray;

typedef struct s_camera
{
	float		x;
	float		y;
	float		dir;
	float		fov;
}				t_camera;


typedef struct s_engine
{
	t_window	*window;
	t_texture	*walls[4];
	t_camera	camera;
	t_map		*map;
	t_list		*entities;
}				t_engine;

void	engine_init(t_engine *engine, t_window *window, t_map *map);
void	render_engine(t_engine *engine);
t_ray	raycast(t_engine *engine, float angle);
void	draw_map(t_engine *engine);

#endif // ENGINE_H
