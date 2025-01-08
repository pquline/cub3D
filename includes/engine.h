/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:37:47 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 11:58:08 by lfarhi           ###   ########.fr       */
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
	t_ray_calc	ray_calc;
	float		camera_plane;
	float		camera_x;
	float		ray_angle;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			screen_x;
	t_texture	*texture;
}			t_rendering;

typedef struct s_camera
{
	float		x;
	float		y;
	float		dir;
	float		fov;
}				t_camera;

typedef struct s_ltxt
{
	int			x;
	t_texture	*texture;
}				t_ltxt;

typedef struct s_engine
{
	void		*game;
	t_window	*window;
	float		*z_buffer;
	t_camera	camera;
	t_map		*map;
	t_list		*entities;
	t_ltxt		(*render_block[LEN_TILE_ID])(struct s_engine *engine, t_rendering *r);
}				t_engine;

typedef struct s_entity t_entity;

typedef struct s_efunc
{
	void		(*update)(t_entity *entity);
	void		(*minimap)(t_entity *entity);
	void		(*free_data)(void *data);
}				t_efunc;

typedef struct s_entity
{
	void		*game;
	t_sprite	*sprites;
	float		pos[2];
	float		dir;
	float		mov_dir;
	float		anim;
	float		anim_map;
	void		*data;
	t_efunc		efunc;
}				t_entity;

t_bool		engine_init(t_engine *engine, t_window *window, t_map *map);
void		destory_engine(t_engine *engine);
void		render_engine(t_engine *engine);
void		render_line(t_engine *engine, t_rendering *r);
void		render_copy(t_rendering *from, t_rendering *to);
t_ray_calc	raycast_calc(t_engine *engine, float angle);
t_ray		raycast(t_engine *engine, float angle);
void		draw_map(t_engine *engine);

void	draw_subtexture_size_z(t_engine *engine,
			t_texture *texture, t_coords coords, float z);

void	draw_sprite_size_angle(t_window *window,
			t_sprite *sprite, t_coords coords, float angle);

void	draw_sprite_mask(t_window *window, t_sprite *sprite, t_coords coords);

t_entity	*spawn_entity(t_engine *engine, void *game, t_efunc efunc, t_sprite *sprites);
void	free_entity(void *entity);
void draw_entities(t_engine *engine);

#endif // ENGINE_H
