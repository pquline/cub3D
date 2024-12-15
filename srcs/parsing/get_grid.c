/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:40:23 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/15 11:11:18 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	door_tile_is_valid(t_parsing *parsing, const char *line, \
	size_t x, size_t y)
{
	if (parsing->map->door_coords[0].x != UNSET)
		return (parsing_error(ERR_DOORS));
	if (x != 0 && ft_isspace(line[x - 1]) == FALSE)
		return (parsing_error(ERR_DOOR_NO_ENDS));
	++x;
	if (line[x] != EMPTY_CHAR)
		return (parsing_error(ERR_DOOR_NO_ACCESS));
	while (line[x] != 0 && line[x] != DOOR_CHAR)
		++x;
	if (line[x] == DOOR_CHAR)
	{
		if (line[x - 1] != EMPTY_CHAR)
			return (parsing_error(ERR_DOOR_NO_ACCESS));
		if (ft_isspace(line[x + 1]) == FALSE)
			return (parsing_error(ERR_DOOR_NO_ENDS));
		parsing->map->door_coords[1] = (t_vector2){x, y};
		return (TRUE);
	}
	return (parsing_error(ERR_DOOR_NO_ENDS));
}

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
		{
			if (door_tile_is_valid(parsing, line, index, y) == FALSE)
				return (FAILURE);
			parsing->map->door_coords[0] = (t_vector2){index, y};
			parsing->map->grid[y][index].id = WALL;
			line[parsing->map->door_coords[1].x] = WALL_CHAR;
		}
		else if (index >= size - sizeof(char) || ft_isspace(line[index]))
			parsing->map->grid[y][index].id = VOID;
		else
			parsing->map->grid[y][index].id = EMPTY;
		parsing->map->grid[y][index].entities = NULL;
		++index;
	}
	return (SUCCESS);
}

t_bool	get_grid(t_parsing *parsing)
{
	size_t	index;
	t_list	*cub;

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
