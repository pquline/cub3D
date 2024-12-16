/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:37:47 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 18:49:34 by lfarhi           ###   ########.fr       */
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
	t_bool		hit;
	float		x;
	float		y;
	float		dir;
	float		dist;
	float		x_t;
	int			side_hit;
	t_tile_id	tile_id;
}				t_ray;

typedef struct s_ray_calc
{
	t_ray		ray;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	float		ray_dir_x;
	float		ray_dir_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			side;
}				t_ray_calc;

typedef struct s_rendering
{
	t_ray		ray;
	float		camera_plane;
	float		camera_x;
	float		ray_angle;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	t_texture	*texture;
}			t_rendering;

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
void	destory_engine(t_engine *engine);
void	render_engine(t_engine *engine);
t_ray	raycast(t_engine *engine, float angle);
void	draw_map(t_engine *engine);

#endif // ENGINE_H
