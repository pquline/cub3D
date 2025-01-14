/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:07:32 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/14 10:35:45 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_bool	parsing_error(char *error)
{
	ft_putendl_fd("Error:", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (FAILURE);
}

static t_bool	init_parsing(t_parsing *parsing)
{
	parsing->map = (t_map *)malloc(sizeof(t_map));
	if (parsing->map == NULL)
		return (parsing_error(ERR_MALLOC_TMAP));
	parsing->map->no = NULL;
	parsing->map->so = NULL;
	parsing->map->we = NULL;
	parsing->map->ea = NULL;
	parsing->map->door = NULL;
	parsing->map->grid = NULL;
	parsing->map->visited = NULL;
	parsing->map->f = UINT_MAX;
	parsing->map->c = UINT_MAX;
	parsing->map->width = 0;
	parsing->map->height = 0;
	parsing->map->start_coords = (t_vector2){UNSET, UNSET};
	parsing->map->start_direction = 0;
	parsing->state = PARSING_METADATA;
	parsing->line = NULL;
	parsing->cub = NULL;
	return (SUCCESS);
}

static t_bool	get_default_door_texture(t_map *map)
{
	if (map->door == NULL)
		map->door = ft_strdup(DEFAULT_DOOR);
	if (map->door == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_map	*parsing(char *path)
{
	t_parsing	parsing;

	if (init_parsing(&parsing) == FAILURE)
		return (NULL);
	if (get_cub(&parsing, path) == FAILURE || get_grid(&parsing) == FAILURE \
		|| get_default_door_texture(parsing.map) == FAILURE)
	{
		free_parsing(&parsing);
		return (free_map(parsing.map));
	}
	free_parsing(&parsing);
	if (map_is_valid(parsing.map) == FALSE)
		return (free_map(parsing.map));
	return (parsing.map);
}
