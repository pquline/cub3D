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

# define SPRITE_SIZE			640
# define MAP_SPRITE_SIZE		48
# define INVULNERABILITY_TIME	10

# define UI_MINIMAP		"assets/UI/minimap.xpm"
# define UI_FONT		"assets/UI/pacman_font.xpm"
# define WORLD_CYAN		"assets/world/cyan.xpm"
# define WORLD_PINK		"assets/world/pink.xpm"
# define WORLD_ORANGE	"assets/world/orange.xpm"
# define WORLD_WHITE	"assets/world/white.xpm"
# define WORLD_RED		"assets/world/red.xpm"
# define WORLD_ORB		"assets/world/orb.xpm"
# define WORLD_BIG_ORB	"assets/world/big_orb.xpm"

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

typedef enum e_visited
{
	VISITED_FALSE,
	VISITED_TRUE,
	VISITED_ORB,
	VISITED_BIG_ORB,
}	t_visited;

typedef struct s_assets
{
	t_sprite	*map_player[6];
	t_sprite	*map_enemy[5];
	t_sprite	*map_orb;
	t_sprite	*map_big_orb;
	t_sprite	*enemy[5][4];
	t_sprite	*door[4];
	t_sprite	*orb[4];
	t_sprite	*big_orb[4];
	t_texture	*map_xpm;
	t_texture	*enemy_xpm[5];
	t_texture	*door_xpm;
	t_texture	*orb_xpm;
	t_texture	*big_orb_xpm;
	t_font		*main_font;
	t_texture	*walls[4];
}	t_assets;

typedef struct s_game
{
	t_window	*window;
	t_engine	engine;
	t_assets	assets;
	float		delta_time;
	t_time		current_time;
	t_time		invulanerability_time;
	t_entity	*player;
	int			remaining_orbs;
}	t_game;

t_time		get_time(void);
float		get_delta(t_time start, t_time end);
int			get_fps(t_time start, t_time end);
float		adaptive_speed(float speed, float delta);

t_bool		want_to_move(t_entity *entity, float x, float y);
t_bool		add_move(t_entity *entity, float x, float y);

int			print_error(char *msg);

t_bool		game_init(t_game *game, t_window *window, t_map *map);
void		destroy_game(t_game *game);
t_bool		load_assets(t_assets *assets, t_map *map, t_window *window);
void		draw_minimap(t_game *game);
t_coords	mask_minimap(t_coords coords);

void		set_entity_pos(t_entity *entity, float x, float y);

void		main_loop(t_window *window, void *data);

void		toggle_door(t_game	*game, int x, int y);
t_bool		door_is_open(t_tile *tile);

t_bool		player_is_invulnerable(t_game *game);

/*Menu*/
void		main_menu_loop(t_window *window, void *data);
void		pause_menu_loop(t_window *window, void *data);
void		gameover_loop(t_window *window, void *data);
void		you_win_loop(t_window *window, void *data);

/*render blocks*/
t_ltxt		render_door(t_engine *engine, t_rendering *r);
t_ltxt		render_wall(t_engine *engine, t_rendering *r);

/*Path finding*/
void		reset_path(t_game *game);
t_bool		exists_path(t_game *game, t_vector2 pos, t_vector2 dest);
t_vector2	move_to(t_game *game, t_vector2 pos, t_vector2 dest);

#endif
