/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:07:32 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/13 10:07:48 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s", (char *)list->content);
		list = list->next;
	}
}

void	print_map(t_map *map)
{
	size_t	x;
	size_t	y;

	if (map == NULL)
		return ;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			printf("%c", map->grid[y][x].id != VOID ? map->grid[y][x].id + '0' : ' ');
			++x;
		}
		printf("\n");
		++y;
	}
}

void	debug_parsing(t_parsing *parsing)
{
	printf("line:\t\t\t[%s]\n", parsing->line);
	printf("state:\t\t\t[%s]\n", parsing->state == PARSING_MAP ? "MAP" : "OTHER");
	printf("map->no:\t\t[%s]\n", parsing->map->no);
	printf("map->so:\t\t[%s]\n", parsing->map->so);
	printf("map->we:\t\t[%s]\n", parsing->map->we);
	printf("map->ea:\t\t[%s]\n", parsing->map->ea);
	printf("map->f.r:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->f).r);
	printf("map->f.g:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->f).g);
	printf("map->f.b:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->f).b);
	printf("map->c.r:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->c).r);
	printf("map->c.g:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->c).g);
	printf("map->c.b:\t\t[%d]\n", mlxe_extract_rgb(parsing->map->c).b);
	printf("map->width:\t\t[%zu]\n", parsing->map->width);
	printf("map->height:\t\t[%zu]\n", parsing->map->height);
	printf("map->start_coords:\t(%d, %d)\n", parsing->map->start_coords.x, \
		parsing->map->start_coords.y);
	printf("map->start_dir:\t\t[%c]\n", parsing->map->start_direction);
	printf("\n");
	print_list(parsing->cub);
	printf("\n");
	print_map(parsing->map);
}

t_map	*parsing(char *path)
{
	t_parsing	parsing;

	init_parsing(&parsing);
	if (parsing.map == NULL)
		return (NULL);
	get_cub(&parsing, path);
	if (parsing.cub == NULL)
	{
		free_map(parsing.map);
		free_parsing(&parsing);
		return (NULL);
	}
	get_grid(&parsing);
	//debug_parsing(&parsing);
	free_parsing(&parsing);
	if (map_is_valid(parsing.map))
		return (parsing.map);
	parsing_error("invalid map");
	free_map(parsing.map);
	return (NULL);
}
