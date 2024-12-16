/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 19:00:25 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <libft.h>
# include <mlxe.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <mlx.h>
# include <time.h>

# include "parsing.h"
# include "engine.h"

typedef struct s_assets
{
	t_sprite	*map_player[6];
	t_sprite	*map_enemy[4];
	t_sprite	*map_coin;
	t_sprite	*enemy[4][4];
	t_sprite	*door[4];
	t_sprite	*coin[4];
	t_texture	*map_xpm;
	t_texture	*enemy_xpm[4];
	t_texture	*door_xpm;
	t_texture	*coin_xpm;
}	t_assets;

typedef struct s_entity	t_entity;

typedef struct s_game
{
	t_window	*window;
	t_engine	engine;
	t_assets	assets;
	char		error_msg[256];
	float		delta_time;
	t_entity	*player;
}	t_game;

typedef struct s_entity
{
	t_game		*game;
	t_sprite	*sprites;
	float		pos[2];
	float		dir;
	float		mov_dir;
	float		anim;
	float		anim_map;
	void		(*update)(struct s_entity *entity);
	void		(*minimap)(struct s_entity *entity);
}				t_entity;

typedef struct timeval t_time;

t_time		get_time();
float		get_delta(t_time start, t_time end);
int			get_fps(t_time start, t_time end);
float		adaptive_speed(float speed, float delta);

t_bool		want_to_move(t_entity *entity, float x, float y);
t_bool		add_move(t_entity *entity, float x, float y);

int			print_error(char *msg);
t_bool		set_error(t_game *game, char *msg);

t_bool		game_init(t_game *game, t_window *window, t_map *map);
void		destroy_game(t_game *game);
t_bool		load_assets(t_assets *assets, t_window *window);
void		draw_minimap(t_game *game);

t_entity	*spawn_entity(t_game *game,
	void (*update)(t_entity *entity),
	void (*minimap)(t_entity *entity),
	t_sprite *sprites);
void		set_entity_pos(t_entity *entity, float x, float y);

void		main_loop(t_window *window, void *data);

#endif
