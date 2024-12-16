/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:35 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 16:21:57 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static t_bool	load_map_assets(t_assets *assets, t_window *window)
{
	assets->map_xpm = mlxe_load_texture(window, "assets/UI/minimap.xpm", TRUE);//TODO check if it's loaded
	if (assets->map_xpm == NULL)
		return (FAILURE);
	assets->map_enemy[0] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){0*48,0,48,48}, TRUE);
	assets->map_enemy[1] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){1*48,0,48,48}, TRUE);
	assets->map_enemy[2] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){2*48,0,48,48}, TRUE);
	assets->map_enemy[3] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){3*48,0,48,48}, TRUE);
	assets->map_player[0] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){4*48,0,48,48}, TRUE);
	assets->map_player[1] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){5*48,0,48,48}, TRUE);
	assets->map_player[2] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){6*48,0,48,48}, TRUE);
	assets->map_player[3] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){7*48,0,48,48}, TRUE);
	assets->map_coin = mlxe_create_sprite(window, assets->map_xpm, (t_rect){8*48,0,48,48}, TRUE);
	assets->map_player[4] = assets->map_player[2];
	assets->map_player[5] = assets->map_player[1];
	return (assets->map_player[0] && assets->map_player[1] \
		&& assets->map_player[2] && assets->map_player[3] \
		&& assets->map_enemy[0] && assets->map_enemy[1] \
		&& assets->map_enemy[2] && assets->map_enemy[3] \
		&& assets->map_coin);
}

static t_bool	load_world_textures(t_assets *assets, t_window *window)
{
	assets->enemy_xpm[0] = mlxe_load_texture(window, \
		"assets/world/blue.xpm", TRUE);
	assets->enemy_xpm[1] = mlxe_load_texture(window, \
		"assets/world/green.xpm", TRUE);
	assets->enemy_xpm[2] = mlxe_load_texture(window, \
		"assets/world/pink.xpm", TRUE);
	assets->enemy_xpm[3] = mlxe_load_texture(window, \
		"assets/world/red.xpm", TRUE);
	assets->door_xpm = mlxe_load_texture(window, "assets/world/door.xpm", TRUE);
	assets->coin_xpm = mlxe_load_texture(window, "assets/world/coin.xpm", TRUE);
	return (assets->enemy_xpm[0] && assets->enemy_xpm[1] && assets->enemy_xpm[2] \
		&& assets->enemy_xpm[3] && assets->door_xpm && assets->coin_xpm);
}

static t_bool	load_world_enemy_sprites(t_assets *assets, t_window *window)
{
	size_t	index_tex;
	size_t	index_sprite;

	index_tex = 0;
	while (index_tex < 4)
	{
		index_sprite = 0;
		while (index_sprite < 4)
		{
			assets->enemy[index_tex][index_sprite] = mlxe_create_sprite(window,\
				assets->enemy_xpm[index_tex], (t_rect){index_sprite * 640, 0, \
				640, 640}, TRUE);
			if (assets->enemy[index_tex][index_sprite] == NULL)
				return (FAILURE);
			++index_sprite;
		}
		++index_tex;
	}
	return (SUCCESS);
}

static t_bool	load_world_door_and_coin_sprites(t_assets *assets, t_window *window)
{
	assets->door[0] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){0 * 640, 0, 640, 640}, TRUE);
	assets->door[1] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){1 * 640, 0, 640, 640}, TRUE);
	assets->door[2] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){2 * 640, 0, 640, 640}, TRUE);
	assets->door[3] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){3 * 640, 0, 640, 640}, TRUE);
	assets->coin[0] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){0 * 640, 0, 640, 640}, TRUE);
	assets->coin[1] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){1 * 640, 0, 640, 640}, TRUE);
	assets->coin[2] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){2 * 640, 0, 640, 640}, TRUE);
	assets->coin[3] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){3 * 640, 0, 640, 640}, TRUE);
	return (assets->door[0] && assets->door[1] && assets->door[2] \
		&& assets->door[3] && assets->coin[0] && assets->coin[1] \
		&& assets->coin[2] && assets->coin[2]);
}

t_bool	load_assets(t_assets *assets, t_window *window)
{
	//printf("player[0]: %p\n", assets->player[0]);
	if (load_map_assets(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_textures(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_enemy_sprites(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_door_and_coin_sprites(assets, window) == FAILURE)
		return (FAILURE);
	assets->player_anim = 0;
	return (SUCCESS);
}
