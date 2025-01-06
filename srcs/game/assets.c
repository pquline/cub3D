/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:35 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/04 12:14:22 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_bool	load_map_sprites(t_texture *texture, t_window *window, \
	t_sprite *sprite[4], size_t offset)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		sprite[index] = mlxe_create_sprite(window, texture, (t_rect){(index + offset) \
			* MAP_SPRITE_SIZE, 0, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, TRUE);
		if (sprite == NULL)
			return (FAILURE);
		++index;
	}
	return (SUCCESS);
}

static t_bool	load_map_assets(t_assets *assets, t_window *window)
{
	assets->map_xpm = mlxe_load_texture(window, "assets/UI/minimap.xpm", TRUE);
	if (assets->map_xpm == NULL)
		return (FAILURE);
	load_map_sprites(assets->map_xpm, window, assets->map_enemy, 0);
	load_map_sprites(assets->map_xpm, window, assets->map_player, 4);
	assets->map_coin = mlxe_create_sprite(window, assets->map_xpm, \
		(t_rect){8 * MAP_SPRITE_SIZE, 0, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, \
		TRUE);
	if (assets->map_coin == NULL)
		return (FAILURE);
	assets->map_player[4] = assets->map_player[2];
	assets->map_player[5] = assets->map_player[1];
	return (SUCCESS);
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
	return (assets->enemy_xpm[0] && assets->enemy_xpm[1] \
		&& assets->enemy_xpm[2] && assets->enemy_xpm[3] && assets->door_xpm \
		&& assets->coin_xpm);
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
				assets->enemy_xpm[index_tex], (t_rect){index_sprite \
				* SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
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
		(t_rect){0 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->door[1] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){1 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->door[2] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){2 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->door[3] = mlxe_create_sprite(window, assets->door_xpm, \
		(t_rect){3 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->coin[0] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){0 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->coin[1] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){1 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->coin[2] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){2 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	assets->coin[3] = mlxe_create_sprite(window, assets->coin_xpm, \
		(t_rect){3 * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
	return (assets->door[0] && assets->door[1] && assets->door[2] \
		&& assets->door[3] && assets->coin[0] && assets->coin[1] \
		&& assets->coin[2] && assets->coin[2]);
}

t_bool	load_assets(t_assets *assets, t_window *window)
{
	if (load_map_assets(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_textures(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_enemy_sprites(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_door_and_coin_sprites(assets, window) == FAILURE)
		return (FAILURE);
	assets->main_font = mlxe_create_font(window, "assets/UI/pacman_font.xpm", TRUE);
	if (assets->main_font == NULL)
		return (FAILURE);
	return (SUCCESS);
}
