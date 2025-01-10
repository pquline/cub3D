/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 16:02:38 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	print_error(char *msg)
{
	ft_putendl_fd("Error :", 2);
	ft_putendl_fd(msg, 2);
	return (1);
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
	window = mlxe_init_fullscreen("cub3D");
	if (!window)
		return (free_map(map), print_error("Failed to initialize window"));
	if (game_init(&game, window, map) == FAILURE)
	{
		free_map(map);
		mlxe_destroy(window);
		return (EXIT_FAILURE);
	}
	mlxe_loop(window, main_menu_loop, &game);
	destroy_game(&game);
	mlxe_destroy(window);
	return (EXIT_SUCCESS);
}
