/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:36:21 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 18:36:28 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
invalid:
- if any tile is neither 0, 1, 2 nor a whitespace
*/
t_bool	parse_map_line(t_parsing *parsing, size_t index)
{
	while (parsing->line[index])
	{
		if (ft_strchr(VALID_MAP_CHARS, parsing->line[index]) == NULL
			&& parsing->line[index] != NL_CHAR)
			return (FALSE);
		if (ft_strchr(PLAYER_MAP_CHARS, parsing->line[index]) != NULL)
		{
			if (parsing->map->start_direction != 0)
				return (FALSE);
			parsing->map->start_direction = parsing->line[index];
			parsing->map->start_coords = (t_vector2){index, \
				parsing->map->height};
		}
		++index;
	}
	if (index - sizeof(char) > parsing->map->width)
		parsing->map->width = index - sizeof(char);
	return (TRUE);
}

t_bool	parse_texture(t_parsing *parsing, char **texture, char *path)
{
	const char	*file_name = ft_strrchr(path, SLASH_CHAR) + sizeof(char);

	if (file_name == NULL)
		return (FALSE);
	*texture = ft_strjoin_safe(parsing->path_prefix, file_name);
	if (*texture == NULL)
		return (FALSE);
	return (TRUE);
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
		return (FALSE);
	++index;
	green = get_primary_color(&line[index], &index);
	if (green == INT_MAX || line[index] != COMMA_CHAR)
		return (FALSE);
	++index;
	blue = get_primary_color(&line[index], &index);
	if (blue == INT_MAX)
		return (FALSE);
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (index != ft_strlen(line))
		return (FALSE);
	*color = mlxe_color(red, green, blue);
	return (TRUE);
}
