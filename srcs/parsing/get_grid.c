/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:40:23 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 12:36:37 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static t_bool	parse_grid_line(t_parsing *parsing, char *line, size_t y)
{
	size_t			index;
	const size_t	size = ft_strlen(line);

	index = 0;
	while (index < parsing->map->width)
	{
		if (index < size && line[index] == WALL_CHAR)
			parsing->map->grid[y][index].id = WALL;
		else if (index < size && line[index] == DOOR_CHAR)
			parsing->map->grid[y][index].id = DOOR;
		else if (index >= size - sizeof(char) || ft_isspace(line[index]))
			parsing->map->grid[y][index].id = VOID;
		else
			parsing->map->grid[y][index].id = EMPTY;
		parsing->map->grid[y][index].data = 0;
		parsing->map->grid[y][index].path_f = 0;
		++index;
	}
	return (SUCCESS);
}

t_bool	get_grid(t_parsing *parsing)
{
	size_t	index;
	t_list	*cub;

	if (parsing->map->width >= INT_MAX || parsing->map->height >= INT_MAX)
		return (parsing_error(ERR_TOO_BIG));
	parsing->map->grid = (t_tile **)ft_calloc(parsing->map->height, \
		sizeof(t_tile *));
	if (parsing->map->grid == NULL)
		return (parsing_error(ERR_MALLOC_TTILES));
	index = 0;
	cub = parsing->cub;
	while (cub != NULL)
	{
		parsing->map->grid[index] = (t_tile *)ft_calloc(parsing->map->width, \
			sizeof(t_tile));
		if (parsing->map->grid[index] == NULL)
			return (parsing_error(ERR_MALLOC_TTILE));
		if (parse_grid_line(parsing, cub->content, index) == FAILURE)
			return (FAILURE);
		cub = cub->next;
		++index;
	}
	return (SUCCESS);
}
