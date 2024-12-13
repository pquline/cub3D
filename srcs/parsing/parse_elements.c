/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:36:21 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/13 10:53:36 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	parse_map_line(t_parsing *parsing, size_t index)
{
	while (parsing->line[index])
	{
		if (ft_strchr(VALID_MAP_CHARS, parsing->line[index]) == NULL
			&& parsing->line[index] != NL_CHAR)
		{
			parsing_error("invalid character in map");
			return (FAILURE);
		}
		if (ft_strchr(PLAYER_MAP_CHARS, parsing->line[index]) != NULL)
		{
			if (parsing->map->start_direction != 0)
			{
				parsing_error("too many player in map");
				return (FAILURE);
			}
			parsing->map->start_direction = parsing->line[index];
			parsing->map->start_coords = (t_vector2){index, \
				parsing->map->height};
		}
		++index;
	}
	if (index - sizeof(char) > parsing->map->width)
		parsing->map->width = index - sizeof(char);
	return (SUCCESS);
}

t_bool	parse_texture(char **texture, char *path)
{
	size_t	index;

	index = 0;
	while (path[index] && ft_isspace(path[index]))
		++index;
	if (path[index] == 0)
	{
		parsing_error("missing texture path");
		return (FAILURE);
	}
	*texture = ft_strndup(&path[index], ft_strlen(&path[index]) - sizeof(char));
	if (*texture == NULL)
	{
		parsing_error("malloc() failed on [char *]");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	get_primary_color(char *line, size_t *i)
{
	size_t	index;
	int		color;

	index = 0;
	while (line[index] && ft_isdigit(line[index]))
		++index;
	if (index >= MIN_RGB_LENGTH && index <= MAX_RGB_LENGTH)
		color = ft_atoi(line);
	else
		return (INT_MAX);
	if (color < MIN_RGB_COLOR || color > MAX_RGB_COLOR)
		return (INT_MAX);
	*i += index;
	return (color);
}

t_bool	parse_color(t_color *color, char *line)
{
	size_t	index;
	int		red;
	int		green;
	int		blue;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		++index;
	red = get_primary_color(&line[index], &index);
	if (red == INT_MAX || line[index] != COMMA_CHAR)
		return (parsing_error("invalid color format"), FAILURE);
	++index;
	green = get_primary_color(&line[index], &index);
	if (green == INT_MAX || line[index] != COMMA_CHAR)
		return (parsing_error("invalid color format"), FAILURE);
	++index;
	blue = get_primary_color(&line[index], &index);
	if (blue == INT_MAX)
		return (parsing_error("invalid color format"), FAILURE);
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (index != ft_strlen(line))
		return (parsing_error("invalid color format"), FAILURE);
	*color = mlxe_color(red, green, blue);
	return (SUCCESS);
}
