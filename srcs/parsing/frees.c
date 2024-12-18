/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:56 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/18 09:48:42 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static void	free_map_grid(t_tile **grid, size_t height)
{
	size_t	index;

	index = 0;
	while (index < height && grid[index] != NULL)
	{
		free(grid[index]);
		++index;
	}
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
	if (map->grid && map->grid[0])
		free_map_grid(map->grid, map->height);
	free(map->grid);
	map->grid = NULL;
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
