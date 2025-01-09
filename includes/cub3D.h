/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/18 15:39:14 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlxe.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <mlx.h>
# include <time.h>

# include <parsing.h>
# include "engine.h"

# define SPRITE_SIZE		640
# define MAP_SPRITE_SIZE	48

typedef struct timeval	t_time;
typedef struct s_entity	t_entity;

typedef enum e_enemy_type
{
	ENEMY_RED,
	ENEMY_CYAN,
	ENEMY_PINK,
	ENEMY_ORANGE,
	ENEMY_WHITE,
}	t_enemy_type;

typedef enum e_enemy_mode
{
	ENEMY_CHASING,
	ENEMY_FRIGHTENED,
}	t_enemy_mode;

typedef struct s_enemy
{
	t_vector2		target;
	t_enemy_type	type;
	t_enemy_mode	mode;
	t_entity		*red;
}	t_enemy;

typedef struct s_assets
{
	t_sprite	*map_player[6];
	t_sprite	*map_enemy[5];
	t_sprite	*map_coin;
	t_sprite	*map_big_orb;
	t_sprite	*enemy[5][4];
	t_sprite	*door[4];
	t_sprite	*coin[4];
	t_sprite	*big_orb[4];
	t_texture	*map_xpm;
	t_texture	*enemy_xpm[5];
	t_texture	*door_xpm;
	t_texture	*coin_xpm;
	t_texture	*big_orb_xpm;
	t_font		*main_font;
	t_texture	*walls[4];
}	t_assets;

typedef struct s_game
{
	t_window	*window;
	t_engine	engine;
	t_assets	assets;
	char		error_msg[256];
	float		delta_time;
	t_time		current_time;
	t_entity	*player;
	int			remaning_orbs;
}	t_game;

t_time		get_time(void);
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
t_coords	mask_minimap(t_coords coords);

void		set_entity_pos(t_entity *entity, float x, float y);

void		main_loop(t_window *window, void *data);

void		toggle_door(t_game	*game, int x, int y);
t_bool		door_is_open(t_tile *tile);

/*Menu*/
void		main_menu_loop(t_window *window, void *data);
void		pause_menu_loop(t_window *window, void *data);
void		gameover_loop(t_window *window, void *data);
void		you_win_loop(t_window *window, void *data);

/*render blocks*/
t_ltxt		render_door(t_engine *engine, t_rendering *r);
t_ltxt		render_wall(t_engine *engine, t_rendering *r);

#endif
