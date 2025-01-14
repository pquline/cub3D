/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/14 12:25:07 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	print_error(char *msg)
{
	ft_putendl_fd("Error:", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

static int	start_game(t_window *window, t_map *map)
{
	t_game		game;

	if (game_init(&game, window, map) == FAILURE)
	{
		free_map(map);
		mlxe_destroy(window);
		return (FAILURE);
	}
	mlxe_loop(window, main_menu_loop, &game);
	destroy_game(&game);
	return (SUCCESS);
}

static t_bool	get_resolution(int ac, char **av, t_vector2 *resolution)
{
	if (ac < 3)
		return (SUCCESS);
	if (ac == 5 && ft_strncmp(av[2], "--resolution", 12) == 0)
	{
		*resolution = (t_vector2){ft_atoi(av[3]), ft_atoi(av[4])};
		return (SUCCESS);
	}
	return (FAILURE);
}

int	main(int ac, char **av)
{
	t_vector2	resolution;
	t_map		*map;
	t_window	*window;

	resolution = (t_vector2){-1, -1};
	if (ac < 2 || get_resolution(ac, av, &resolution) == FAILURE)
		return (print_error("Usage: ./cub3D [map.cub]"));
	map = parsing(av[1]);
	if (map == NULL)
		return (EXIT_FAILURE);
	if (resolution.x < 0 || resolution.y < 0)
		window = mlxe_init_fullscreen("cub3D");
	else
		window = mlxe_init(resolution.x, resolution.y, "cub3D");
	if (!window)
		return (free_map(map), print_error("Failed to initialize window"));
	if (start_game(window, map) == FAILURE)
		return (EXIT_FAILURE);
	mlxe_destroy(window);
	return (EXIT_SUCCESS);
}
