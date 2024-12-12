/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:37:47 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 14:06:09 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <libft.h>
# include <mlxe.h>
# include "parsing.h"

# include <sys/time.h>
# include <math.h>
# define M_PI 3.14159265358979323846
# define M_PI_2 1.57079632679489661923

typedef struct s_ray
{
	float		x;
	float		y;
	float		dir;
	float		dist;
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

#endif // ENGINE_H