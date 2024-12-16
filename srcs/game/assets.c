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
	(void)assets;
	(void)window;
	return (SUCCESS);
}

t_bool	load_assets(t_assets *assets, t_window *window)
{
	assets->map_xpm = mlxe_load_texture(window, "assets/UI/minimap.xpm", TRUE);//TODO check if it's loaded
	if (assets->map_xpm == NULL)
		return (FAILURE);
	//printf("minimap_entities: %p\n", assets->minimap_entities);
	assets->map_player[0] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){192,0,48,48}, TRUE);
	assets->map_player[1] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){240,0,48,48}, TRUE);
	assets->map_player[2] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){288,0,48,48}, TRUE);
	assets->map_player[3] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){336,0,48,48}, TRUE);
	assets->map_player[4] = assets->map_player[2];
	assets->map_player[5] = assets->map_player[1];
	assets->map_enemy[0] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){0,0,48,48}, TRUE);
	assets->map_enemy[1] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){48,0,48,48}, TRUE);
	assets->map_enemy[2] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){96,0,48,48}, TRUE);
	assets->map_enemy[3] = mlxe_create_sprite(window, assets->map_xpm, (t_rect){144,0,48,48}, TRUE);
	assets->map_pellet = mlxe_create_sprite(window, assets->map_xpm, (t_rect){384,0,48,48}, TRUE);
	if (!assets->map_player[0] || !assets->map_player[1] \
			|| !assets->map_player[2] || !assets->map_player[3] \
			|| !assets->map_enemy[0] || !assets->map_enemy[1] \
			|| !assets->map_enemy[2] || !assets->map_enemy[3] \
			|| !assets->map_pellet)
		return (FAILURE);
	assets->player_anim = 0;
	//printf("player[0]: %p\n", assets->player[0]);
	load_map_assets(assets, window);
	return (SUCCESS);
}
