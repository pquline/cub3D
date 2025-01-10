/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:35 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 15:46:03 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_bool	load_map_sprites(t_texture *texture, t_window *window, \
	t_sprite **sprite, t_vector2 offset_count)
{
	int	index;

	index = 0;
	while (index < offset_count.y)
	{
		sprite[index] = mlxe_create_sprite(window, texture,
				(t_rect){(index + offset_count.x) * MAP_SPRITE_SIZE, 0,
				MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, TRUE);
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
	if (load_map_sprites(assets->map_xpm, window, \
			assets->map_enemy, (t_vector2){0, 5}) == FAILURE)
		return (FAILURE);
	if (load_map_sprites(assets->map_xpm, window, \
			assets->map_player, (t_vector2){5, 4}) == FAILURE)
		return (FAILURE);
	assets->map_orb = mlxe_create_sprite(window, assets->map_xpm, \
		(t_rect){9 * MAP_SPRITE_SIZE, 0, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, \
		TRUE);
	assets->map_big_orb = mlxe_create_sprite(window, assets->map_xpm, \
		(t_rect){10 * MAP_SPRITE_SIZE, 0, MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, \
		TRUE);
	if (assets->map_orb == NULL || assets->map_big_orb == NULL)
		return (FAILURE);
	assets->map_player[4] = assets->map_player[2];
	assets->map_player[5] = assets->map_player[1];
	return (SUCCESS);
}

static t_bool	load_world_textures(t_assets *assets, t_window *window)
{
	assets->enemy_xpm[ENEMY_RED] = mlxe_load_texture(window, \
		"assets/world/red.xpm", TRUE);
	assets->enemy_xpm[ENEMY_CYAN] = mlxe_load_texture(window, \
		"assets/world/cyan.xpm", TRUE);
	assets->enemy_xpm[ENEMY_PINK] = mlxe_load_texture(window, \
		"assets/world/pink.xpm", TRUE);
	assets->enemy_xpm[ENEMY_ORANGE] = mlxe_load_texture(window, \
		"assets/world/orange.xpm", TRUE);
	assets->enemy_xpm[ENEMY_WHITE] = mlxe_load_texture(window, \
		"assets/world/white.xpm", TRUE);
	assets->door_xpm = mlxe_load_texture(window, "assets/world/door.xpm", TRUE);
	assets->orb_xpm = mlxe_load_texture(window, "assets/world/orb.xpm", TRUE);
	assets->big_orb_xpm = mlxe_load_texture(window, \
		"assets/world/big_orb.xpm", TRUE);
	return (assets->enemy_xpm[ENEMY_RED] && assets->enemy_xpm[ENEMY_CYAN] \
		&& assets->enemy_xpm[ENEMY_PINK] && assets->enemy_xpm[ENEMY_ORANGE] \
		&& assets->enemy_xpm[ENEMY_WHITE] && assets->door_xpm \
		&& assets->orb_xpm && assets->big_orb_xpm);
}

static t_bool	load_world_enemy_sprites(t_assets *assets, t_window *window)
{
	size_t	index_tex;
	size_t	index_sprite;

	index_tex = 0;
	while (index_tex < 5)
	{
		index_sprite = 0;
		while (index_sprite < 4)
		{
			assets->enemy[index_tex][index_sprite] = mlxe_create_sprite(window,
					assets->enemy_xpm[index_tex], (t_rect){index_sprite
					* SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
			if (assets->enemy[index_tex][index_sprite] == NULL)
				return (FAILURE);
			++index_sprite;
		}
		++index_tex;
	}
	return (SUCCESS);
}

static t_bool	load_four_sprites(t_sprite **sprite, t_window *window, \
	t_texture *texture)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		sprite[index] = mlxe_create_sprite(window, texture, \
			(t_rect){index * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE}, TRUE);
		if (sprite[index] == NULL)
			return (FAILURE);
		++index;
	}
	return (SUCCESS);
}

static t_bool	load_world_door_and_orb_sprites(t_assets *assets, \
	t_window *window)
{
	if (load_four_sprites(assets->door, window, assets->door_xpm) == FAILURE)
		return (FAILURE);
	if (load_four_sprites(assets->orb, window, assets->orb_xpm) == FAILURE)
		return (FAILURE);
	if (load_four_sprites(assets->big_orb,
			window, assets->big_orb_xpm) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_bool	load_assets(t_assets *assets, t_window *window)
{
	if (load_map_assets(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_textures(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_enemy_sprites(assets, window) == FAILURE)
		return (FAILURE);
	if (load_world_door_and_orb_sprites(assets, window) == FAILURE)
		return (FAILURE);
	assets->main_font = mlxe_create_font(window,
			"assets/UI/pacman_font.xpm", TRUE);
	if (assets->main_font == NULL)
		return (FAILURE);
	return (SUCCESS);
}
