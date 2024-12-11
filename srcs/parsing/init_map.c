/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:04 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 21:14:26 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = init_map();
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (parsing_error("malloc() failed on [t_map *]"));
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->grid = NULL;
	map->f = mlxe_color(MIN_RGB_COLOR, MIN_RGB_COLOR, MIN_RGB_COLOR);
	map->c = mlxe_color(MIN_RGB_COLOR, MIN_RGB_COLOR, MIN_RGB_COLOR);
	map->width = 0;
	map->height = 0;
	map->start_coords = (t_vector2){-1, -1};
	map->start_direction = 0;
	return (map);
}
