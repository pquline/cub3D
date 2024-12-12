/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 19:08:55 by lfarhi           ###   ########.fr       */
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

# include "parsing.h"
# include "engine.h"

typedef struct s_assets
{
	t_texture	*minimap_entities;
	t_sprite	*player[6];
	float		player_anim;
}	t_assets;

typedef struct s_game
{
	t_window	*window;
	t_engine	engine;
	t_assets	assets;
	char		error_msg[256];
}	t_game;

int			print_error(char *msg);
t_bool		set_error(t_game *game, char *msg);

t_bool		game_init(t_game *game, t_window *window, t_map *map);
t_bool	load_assets(t_assets *assets, t_window *window);
void draw_minimap(t_game *game);

void		main_loop(t_window *window, void *data);

#endif
