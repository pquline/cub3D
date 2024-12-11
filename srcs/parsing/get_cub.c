/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:01:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 21:34:33 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_single_color(char *line, size_t *i)
{
	size_t	index;
	int		color;

	index = 0;
	while (line[index] && ft_isdigit(line[index]))
		++index;
	if (index > 0 && index <= 3)
		color = ft_atoi(line);
	else
		return (INT_MAX);
	if (color < MIN_RGB_COLOR || color > MAX_RGB_COLOR)
		return (INT_MAX);
	*i += index;
	return (color);
}

t_bool	parse_colors(t_color *color, char *line)
{
	size_t	index;
	int		red;
	int		green;
	int		blue;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		++index;
	red = get_single_color(&line[index], &index);
	if (red == INT_MAX || line[index] != COMMA_CHAR)
		return (FALSE);
	++index;
	green = get_single_color(&line[index], &index);
	if (green == INT_MAX || line[index] != COMMA_CHAR)
		return (FALSE);
	++index;
	blue = get_single_color(&line[index], &index);
	if (blue == INT_MAX)
		return (FALSE);
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (index != ft_strlen(line))
		return (FALSE);
	color = (t_color){red, green, blue};
	return (TRUE);
}

t_bool	parse_cub_line(t_map *map, t_list **cub, char *line)
{
	size_t	index;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (ft_strncmp(&line[index], COLOR_FLOOR, 1) == 0)
		return (parse_colors(&map->f, &line[index + 1]));
	if (ft_strncmp(&line[index], COLOR_CEILING, 1) == 0)
		return (parse_colors(&map->c, &line[index + 1]));
	if (ft_strncmp(&line[index], TEXTURE_NORTH, 2) == 0)
		return (parse_north(map, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_SOUTH, 2) == 0)
		return (parse_south(map, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_WEST, 2) == 0)
		return (parse_west(map, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_EAST, 2) == 0)
		return (parse_east(map, &line[index + 2]));
	if (index == 0 && ft_strlen(line) == 0 && *line == NULL)
		return (TRUE);
	return (FALSE);
}

void	parse_cub(t_map *map, t_list **cub, int fd)
{
	char	*line;
	t_bool	valid;
	t_list	*new;

	line = get_next_line(fd);
	while (line != NULL)
	{
		valid = parse_cub_line(map, cub, line);
		if (valid == FALSE)
		{
			free(line);
			ft_lstclear(cub, free);
			return (NULL);
		}
		new = ft_lstnew(line);
		if (new == NULL)
		{
			free(line);
			ft_lstclear(cub, free);
			return (parsing_error("malloc() failed on [t_list *]"));
		}
		ft_lstadd_back(cub, new);
		line = get_next_line(fd);
	}
}

t_list	*get_cub(t_map *map, char *path)
{
	int		fd;
	t_list	*cub;

	cub = NULL;
	fd = open(path, O_RDONLY);
	if (fd == ERROR)
		return (parsing_error("open() failed"));
	parse_cub(map, &cub, fd);
	if (cub == NULL)
		return (NULL);
	if (close(fd) == ERROR)
	{
		ft_lstclear(&cub, free);
		return (parsing_error("close() failed"));
	}
	return (cub);
}
