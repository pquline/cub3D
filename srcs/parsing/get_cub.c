/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:01:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 18:37:36 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	parse_cub_line(t_parsing *parsing, t_map *map, char *line)
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
		return (parse_map_line(parsing, index));
	parsing_error("invalid .cub file format");
	return (FALSE);
}

static void	update_parsing_state(t_parsing *parsing)
{
	if (parsing->state == PARSING_MAP)
		return ;
	if (parsing->map->f != UINT_MAX && parsing->map->c != UINT_MAX \
			&& parsing->map->no != NULL && parsing->map->so != NULL \
			&& parsing->map->we != NULL && parsing->map->ea != NULL \
			&& parsing->line[0] != NL_CHAR)
		parsing->state = PARSING_MAP;
}

static void	parse_cub(t_parsing *parsing, int fd)
{
	t_list	*new;

	parsing->line = get_next_line(fd);
	while (parsing->line != NULL)
	{
		update_parsing_state(parsing);
		if (parse_cub_line(parsing, parsing->map, parsing->line) == FALSE)
			return ;
		if (parsing->state == PARSING_MAP)
		{
			new = ft_lstnew(parsing->line);
			if (new == NULL)
			{
				parsing_error("malloc() failed on [t_list *]");
				return ;
			}
			ft_lstadd_back(&parsing->cub, new);
			++parsing->map->height;
		}
		else
			free(parsing->line);
		parsing->line = get_next_line(fd);
	}
}

/*
/home/user/map.cub
../maps/map.cub
../map.cub
./map.cub
map.cub
*/
static void	extract_path(t_parsing *parsing, char *path)
{
	const char	*file_name = ft_strrchr(path, SLASH_CHAR);

	if (file_name == NULL)
		return ;
	parsing->path_prefix = ft_strndup(path, file_name - path + sizeof(char));
}

void	get_cub(t_parsing *parsing, char *path)
{
	int	fd;

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
