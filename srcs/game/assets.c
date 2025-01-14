/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:35 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/14 10:33:05 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static t_bool	load_map_sprites(t_texture *texture, t_window *window, \
	t_sprite **sprite, t_vector2 offset)
{
	int	index;

	index = 0;
	while (index < offset.y)
	{
		sprite[index] = mlxe_create_sprite(window, texture,
				(t_rect){(index + offset.x) * MAP_SPRITE_SIZE, 0,
				MAP_SPRITE_SIZE, MAP_SPRITE_SIZE}, TRUE);
		if (sprite == NULL)
			return (FAILURE);
		++index;
	}
	return (SUCCESS);
}

static t_bool	load_map_assets(t_assets *assets, t_window *window)
{
	assets->map_xpm = mlxe_load_texture(window, UI_MINIMAP, TRUE);
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

static t_bool	load_world_textures(t_assets *assets, t_map *map, t_window *w)
{
	assets->walls[0] = mlxe_load_texture(w, map->no, TRUE);
	assets->walls[1] = mlxe_load_texture(w, map->ea, TRUE);
	assets->walls[2] = mlxe_load_texture(w, map->so, TRUE);
	assets->walls[3] = mlxe_load_texture(w, map->we, TRUE);
	assets->enemy_xpm[ENEMY_RED] = mlxe_load_texture(w, WORLD_RED, TRUE);
	assets->enemy_xpm[ENEMY_CYAN] = mlxe_load_texture(w, WORLD_CYAN, TRUE);
	assets->enemy_xpm[ENEMY_PINK] = mlxe_load_texture(w, WORLD_PINK, TRUE);
	assets->enemy_xpm[ENEMY_ORANGE] = mlxe_load_texture(w, WORLD_ORANGE, TRUE);
	assets->enemy_xpm[ENEMY_WHITE] = mlxe_load_texture(w, WORLD_WHITE, TRUE);
	assets->door_xpm = mlxe_load_texture(w, map->door, TRUE);
	assets->orb_xpm = mlxe_load_texture(w, WORLD_ORB, TRUE);
	assets->big_orb_xpm = mlxe_load_texture(w, WORLD_BIG_ORB, TRUE);
	return (assets->walls[0] && assets->walls[1] && assets->walls[2] \
		&& assets->walls[3] && assets->enemy_xpm[ENEMY_RED]
		&& assets->enemy_xpm[ENEMY_CYAN] \
		&& assets->enemy_xpm[ENEMY_PINK] && assets->enemy_xpm[ENEMY_ORANGE] \
		&& assets->enemy_xpm[ENEMY_WHITE] && assets->door_xpm \
		&& assets->orb_xpm && assets->big_orb_xpm);
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

t_bool	load_assets(t_assets *assets, t_map *map, t_window *w)
{
	size_t	index;

	if (load_map_assets(assets, w) == FAILURE)
		return (FAILURE);
	if (load_world_textures(assets, map, w) == FAILURE)
		return (FAILURE);
	index = 0;
	while (index < 5)
	{
		if (load_four_sprites(assets->enemy[index], w, \
				assets->enemy_xpm[index]) == FAILURE)
			return (FAILURE);
		++index;
	}
	if (load_four_sprites(assets->door, w, assets->door_xpm) == FAILURE)
		return (FAILURE);
	if (load_four_sprites(assets->orb, w, assets->orb_xpm) == FAILURE)
		return (FAILURE);
	if (load_four_sprites(assets->big_orb, w, assets->big_orb_xpm) == FAILURE)
		return (FAILURE);
	assets->main_font = mlxe_create_font(w, UI_FONT, TRUE);
	if (assets->main_font == NULL)
		return (FAILURE);
	return (SUCCESS);
}
