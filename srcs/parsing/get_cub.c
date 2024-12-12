/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:01:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 15:49:52 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_bool	parse_map_line(t_map *map)
{
	(void)map;
	return (TRUE);
}

/*
- get texture path
- join path_prefix and texture path
*/
t_bool	parse_texture(t_parsing *parsing, char **texture, char *path)
{
	const char	*file_name = ft_strrchr(path, SLASH_CHAR);

	if (file_name == NULL)
		return (FALSE);
	*texture = ft_strjoin_safe(parsing->path_prefix, file_name);
	if (*texture == NULL)
		return (FALSE);
	return (TRUE);
}

int	get_primary_color(char *line, size_t *i)
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

t_bool	parse_cub_line(t_parsing *parsing, t_map *map, char *line)
{
	size_t	index;

	index = 0;
	if (parsing->state == PARSING_OTHER && line[0] == NL_CHAR)
		return (TRUE);
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (ft_strncmp(&line[index], COLOR_FLOOR, 1) == 0)
		return (map->f == UINT_MAX && parse_color(&map->f, &line[index + 1]));
	if (ft_strncmp(&line[index], COLOR_CEILING, 1) == 0)
		return (map->c == UINT_MAX && parse_color(&map->c, &line[index + 1]));
	if (ft_strncmp(&line[index], TEXTURE_NORTH, 2) == 0)
		return (parse_texture(parsing, &map->no, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_SOUTH, 2) == 0)
		return (parse_texture(parsing, &map->so, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_WEST, 2) == 0)
		return (parse_texture(parsing, &map->we, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_EAST, 2) == 0)
		return (parse_texture(parsing, &map->ea, &line[index + 2]));
	if (parsing->state == PARSING_MAP && line[0] != NL_CHAR)
		return (parse_map_line(map));
	return (FALSE);
}

void	update_parsing_state(t_parsing *parsing)
{
	if (parsing->state == PARSING_MAP)
		return ;
	if (parsing->map->f != UINT_MAX && parsing->map->c != UINT_MAX \
			&& parsing->map->no != NULL && parsing->map->so != NULL \
			&& parsing->map->we != NULL && parsing->map->ea != NULL \
			&& parsing->line[0] != NL_CHAR)
		parsing->state = PARSING_MAP;
}

void	parse_cub(t_parsing *parsing, int fd)
{
	t_list	*new;

	parsing->line = get_next_line(fd);
	while (parsing->line != NULL)
	{
		update_parsing_state(parsing);
		if (parse_cub_line(parsing, parsing->map, parsing->line) == FALSE)
		{
			parsing_error("invalid .cub file format");
			return ;
		}
		new = ft_lstnew(parsing->line);
		if (new == NULL)
		{
			parsing_error("malloc() failed on [t_list *]");
			return ;
		}
		ft_lstadd_back(&parsing->cub, new);
		parsing->line = get_next_line(fd);
	}
}

/*
/home/pfischof/map.cub
../maps/map.cub
../map.cub
./map.cub
map.cub
*/
void	extract_path(t_parsing *parsing, char *path)
{
	const char	*file_name = ft_strrchr(path, SLASH_CHAR);

	if (file_name == NULL)
		return ;
	parsing->path_prefix = ft_strndup(path, file_name - path + sizeof(char));
}

void	get_cub(t_parsing *parsing, char *path)
{
	int		fd;

	if (ft_strncmp(&path[ft_strlen(path) - SIZE_EXT], CUB_EXT, SIZE_EXT) != 0)
	{
		parsing_error("invalid .cub file name");
		return ;
	}
	extract_path(parsing, path);
	fd = open(path, O_RDONLY);
	if (fd == ERROR)
	{
		parsing_error("open() failed");
		return ;
	}
	parse_cub(parsing, fd);
	close(fd);
}
