/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:56 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 14:38:43 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_map_grid(t_tile ***grid, size_t height)
{
	size_t	index;

	index = 0;
	while (index < height)
	{
		free(*grid[index]);
		*grid[index] = NULL;
		++index;
	}
	free(*grid);
	*grid = NULL;
}

void	*free_map(t_map *map)
{
	if (map == NULL)
		return (NULL);
	free(map->no);
	map->no = NULL;
	free(map->so);
	map->no = NULL;
	free(map->we);
	map->no = NULL;
	free(map->ea);
	map->no = NULL;
	if (map->grid)
		free_map_grid(&map->grid, map->height);
	free(map);
	return (NULL);
}

void	*free_parsing(t_parsing *parsing)
{
	ft_lstclear(&parsing->cub, free);
	free(parsing->line);
	parsing->line = NULL;
	return (NULL);
}
