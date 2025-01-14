/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:56 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/14 10:22:43 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_bool	free_double_array(void **array, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		free(array[index]);
		++index;
	}
	return (FAILURE);
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
	free(map->door);
	map->door = NULL;
	if (map->grid && map->grid[0])
		free_double_array((void **)map->grid, map->height);
	free(map->grid);
	map->grid = NULL;
	if (map->visited && map->visited[0])
		free_double_array((void **)map->visited, map->height);
	free(map->visited);
	map->visited = NULL;
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
