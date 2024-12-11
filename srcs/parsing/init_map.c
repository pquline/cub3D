/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:04 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 16:31:11 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = init_map();
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (parsing_error("malloc failed on [t_map *]"));
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->grid = NULL;
	map->f = mlxe_color(0, 0, 0);
	map->c = mlxe_color(0, 0, 0);
	map->width = 0;
	map->height = 0;
	map->player_coords = (t_vector2){0, 0};
	map->direction = 0;
	return (map);
}
