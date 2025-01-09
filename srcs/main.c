/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/09 15:47:50 by pfischof         ###   ########.fr       */
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
