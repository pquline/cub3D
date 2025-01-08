/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 15:04:23 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	print_error(char *msg)
{
	ft_putendl_fd("Error :", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

t_bool	set_error(t_game *game, char *msg)
{
	size_t	len;

	if (!*game->error_msg)
	{
		len = ft_strlen(msg);
		if (len > 254)
			len = 254;
		ft_strlcpy(game->error_msg, msg, len + 1);
		game->error_msg[len] = '\0';
	}
	return (FAILURE);
}

t_map* test_map()
{
	t_map *map = malloc(sizeof(t_map));
	map->no = "./assets/tests/missing_n.xpm";
	map->so = "./assets/tests/missing_s.xpm";
	map->we = "./assets/tests/missing_w.xpm";
	map->ea = "./assets/tests/missing_e.xpm";
	map->c = mlxe_color(139, 170, 173);
	map->f = mlxe_color(77, 77, 71);
	map->width = 10;
	map->height = 10;
	map->grid = malloc(sizeof(t_tile *) * map->height);
	for (size_t i = 0; i < map->height; i++)
	{
		map->grid[i] = malloc(sizeof(t_tile) * map->width);
		for (size_t j = 0; j < map->width; j++)
		{
			map->grid[i][j].id = EMPTY;
		}
	}
	for (size_t i = 0; i < map->height; i++)
	{
		map->grid[i][0].id = WALL;
		map->grid[i][map->width - 1].id = WALL;
	}
	for (size_t j = 0; j < map->width; j++)
	{
		map->grid[0][j].id = WALL;
		map->grid[map->height - 1][j].id = WALL;
	}
	//spawn random WALL
	//reset random seed
	struct timeval tv;
    struct timezone tz;
	gettimeofday(&tv, &tz);
	srand(tv.tv_usec);
	for (size_t i = 1; i < map->height - 1; i++)
	{
		for (size_t j = 1; j < map->width - 1; j++)
		{
			if (rand() % 5 == 0)
				map->grid[i][j].id = WALL;
		}
	}
	map->grid[5][5].id = EMPTY;
	map->start_coords = (t_vector2){5, 5};
	map->start_direction = 'N';
	return map;
}

int	main(int ac, char **av)
{
	t_game		game;
	t_map		*map;
	t_window	*window;

	if (ac != 2)
		return (print_error("Usage : ./cub3D [map.cub]"));
	map = parsing(av[1]);
	if (map == NULL)
		return (EXIT_FAILURE);
	//return (free_map(map), EXIT_SUCCESS);
	//window = mlxe_init(1920 / 1.5, 1080 / 1.5, "cub3d");
	window = mlxe_init_fullscreen("cub3d");
	if (!window)
		return (free_map(map), print_error("Failed to initialize window"));
	if (game_init(&game, window, map) == FAILURE)
	{
		free_map(map);
		mlxe_destroy(window);
		return (EXIT_FAILURE);
	}
	mlxe_loop(window, main_menu_loop, &game);

	//error = FAILURE;
	//set_error(&game, "Test error");
	destroy_game(&game);
	mlxe_destroy(window);
	// if (!error)
	// 	return (print_error(game.error_msg));
	return (EXIT_SUCCESS);
}
