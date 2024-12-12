/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:40:23 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 20:44:59 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_list_content(t_list *list, size_t node)
{
	size_t	index;

	index = 0;
	while (list != NULL && index < node)
	{
		list = list->next;
		++index;
	}
	if (list != NULL)
		return (list->content);
	return (NULL);
}

static void	parse_grid_line(t_parsing *parsing, size_t y)
{
	size_t			index;
	const char		*line = get_list_content(parsing->cub, y);
	const size_t	size = ft_strlen(line);

	index = 0;
	while (index < parsing->map->width)
	{
		if (index < size && line[index] == EMPTY_CHAR)
			parsing->map->grid[y][index].id = EMPTY;
		else if (index < size && line[index] == WALL_CHAR)
			parsing->map->grid[y][index].id = WALL;
		else if (index < size && line[index] == DOOR_CHAR)
			parsing->map->grid[y][index].id = DOOR;
		else if (index >= size - sizeof(char) || line[index] == SPACE_CHAR)
			parsing->map->grid[y][index].id = VOID;
		else
			parsing->map->grid[y][index].id = EMPTY;
		parsing->map->grid[y][index].entities = NULL;
		++index;
	}
}

void	get_grid(t_parsing *parsing)
{
	size_t	index;

	parsing->map->grid = (t_tile **)ft_calloc(parsing->map->height, \
		sizeof(t_tile *));
	if (parsing->map->grid == NULL)
	{
		parsing_error("malloc() failed on [t_tile **]");
		return ;
	}
	index = 0;
	while (index < parsing->map->height)
	{
		parsing->map->grid[index] = (t_tile *)ft_calloc(parsing->map->width, \
			sizeof(t_tile));
		if (parsing->map->grid[index] == NULL)
		{
			parsing_error("malloc() failed on [t_tile *]");
			return ;
		}
		parse_grid_line(parsing, index);
		++index;
	}
}
