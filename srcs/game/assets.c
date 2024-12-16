/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:35 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 18:38:52 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_bool	load_assets(t_assets *assets, t_window *window)
{
	assets->minimap_entities = mlxe_load_texture(window, "assets/UI/minimap_entities.xpm", TRUE);//TODO check if it's loaded
	//printf("minimap_entities: %p\n", assets->minimap_entities);
	assets->player[0] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){0,0,48,44}, TRUE);
	assets->player[1] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){58,0,48,44}, TRUE);
	assets->player[2] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){118,0,48,44}, TRUE);
	assets->player[3] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){178,0,48,44}, TRUE);
	assets->player[4] = assets->player[2];
	assets->player[5] = assets->player[1];
	//printf("player[0]: %p\n", assets->player[0]);
	return (SUCCESS);
}
