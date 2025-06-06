/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:01:32 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/14 10:23:13 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static t_bool	parse_cub_line(t_parsing *parsing, t_map *map, char *line)
{
	size_t	index;

	index = 0;
	if (parsing->state == PARSING_METADATA && line[0] == NL_CHAR)
		return (SUCCESS);
	while (line[index] && ft_isspace(line[index]))
		++index;
	if (ft_strncmp(&line[index], COLOR_FLOOR, 1) == 0)
		return (parse_color(&map->f, &line[index + 1]));
	if (ft_strncmp(&line[index], COLOR_CEILING, 1) == 0)
		return (parse_color(&map->c, &line[index + 1]));
	if (ft_strncmp(&line[index], TEXTURE_NORTH, 2) == 0)
		return (parse_texture(&map->no, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_SOUTH, 2) == 0)
		return (parse_texture(&map->so, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_WEST, 2) == 0)
		return (parse_texture(&map->we, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_EAST, 2) == 0)
		return (parse_texture(&map->ea, &line[index + 2]));
	if (ft_strncmp(&line[index], TEXTURE_DOOR, 2) == 0)
		return (parse_texture(&map->door, &line[index + 2]));
	if (parsing->state == PARSING_MAP && line[0] != NL_CHAR)
		return (parse_map_line(parsing, index));
	return (parsing_error(ERR_CUB_FORMAT));
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

static t_bool	parse_cub(t_parsing *parsing, int fd)
{
	t_list	*new;

	parsing->line = get_next_line(fd);
	while (parsing->line != NULL)
	{
		update_parsing_state(parsing);
		if (parse_cub_line(parsing, parsing->map, parsing->line) == FAILURE)
			return (FAILURE);
		if (parsing->state == PARSING_MAP)
		{
			new = ft_lstnew(parsing->line);
			if (new == NULL)
				return (parsing_error(ERR_MALLOC_TLIST));
			ft_lstadd_back(&parsing->cub, new);
			++parsing->map->height;
		}
		else
			free(parsing->line);
		parsing->line = get_next_line(fd);
	}
	return (SUCCESS);
}

t_bool	get_cub(t_parsing *parsing, char *path)
{
	int				fd;
	const size_t	length = ft_strlen(path);

	if (length < CUB_LENGTH || ft_strncmp(&path[length - CUB_LENGTH], \
			CUB_SUFFIX, CUB_LENGTH) != 0)
		return (parsing_error(ERR_CUB_SUFFIX));
	fd = open(path, O_RDONLY);
	if (fd == ERROR)
		return (parsing_error(ERR_CUB_OPEN));
	if (parse_cub(parsing, fd) == FAILURE)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
