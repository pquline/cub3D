/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:36:21 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 12:51:29 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_bool	parse_map_line(t_parsing *parsing, size_t index)
{
	while (parsing->line[index])
	{
		if (ft_strchr(VALID_MAP_CHARS, parsing->line[index]) == NULL \
				&& parsing->line[index] != NL_CHAR)
			return (parsing_error(ERR_INVALID_CHAR));
		if (ft_strchr(PLAYER_MAP_CHARS, parsing->line[index]) != NULL)
		{
			if (parsing->map->start_direction != 0)
				return (parsing_error(ERR_PLAYERS));
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

	if (*texture != NULL)
		return (parsing_error(ERR_TEXTURE_MULT));
	index = 0;
	while (path[index] && ft_isspace(path[index]))
		++index;
	if (path[index] == 0)
		return (parsing_error(ERR_TEXTURE_PATH));
	*texture = ft_strndup(&path[index], ft_strlen(&path[index]) - sizeof(char));
	if (*texture == NULL)
		return (parsing_error(ERR_MALLOC_STRING));
	return (SUCCESS);
}

static int	get_primary_color(char *line, size_t *i)
{
	size_t	index;
	int		color;

	index = 0;
	while (line[index] && ft_isdigit(line[index]))
		++index;
	if (index < MIN_RGB_LENGTH || index > MAX_RGB_COLOR)
		return (INT_MAX);
	color = ft_atoi(line);
	if (color < MIN_RGB_COLOR || color > MAX_RGB_COLOR)
		return (INT_MAX);
	*i += index;
	return (color);
}

t_bool	parse_color(t_color *result, char *line)
{
	int			primary[3];
	size_t		index;
	t_primary	color;

	index = 0;
	color = RED;
	if (*result != UINT_MAX)
		return (parsing_error(ERR_COLOR_MULT));
	while (color < PRIMARY_END)
	{
		while (line[index] && ft_isspace(line[index]))
			++index;
		primary[color] = get_primary_color(&line[index], &index);
		if (primary[color] == INT_MAX \
				|| (color < BLUE && line[index] != COMMA_CHAR))
			return (parsing_error(ERR_COLOR));
		if (color < BLUE)
			++index;
		++color;
	}
	if (index != ft_strlen(line) - sizeof(char))
		return (parsing_error(ERR_COLOR));
	*result = mlxe_color(primary[RED], primary[GREEN], primary[BLUE]);
	return (SUCCESS);
}
