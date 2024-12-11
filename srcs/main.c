/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/11 16:37:59 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

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

t_bool	game_init(t_game *game, t_window *window, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window = window;
	engine_init(&game->engine, window, map);
	return (SUCCESS);
}

t_map* test_map()
{
	t_map *map = malloc(sizeof(t_map));
	map->no = "textures/wood.xpm";
	map->so = "textures/wood.xpm";
	map->we = "textures/wood.xpm";
	map->ea = "textures/wood.xpm";
	map->c = mlxe_color(139, 170, 173);
	map->f = mlxe_color(77, 77, 71);
	map->grid = malloc(sizeof(t_tile *) * 10);
	for (size_t i = 0; i < 10; i++)
	{
		map->grid[i] = malloc(sizeof(t_tile) * 10);
		for (size_t j = 0; j < 10; j++)
		{
			map->grid[i][j] = EMPTY;
		}
	}
	map->width = 10;
	map->height = 10;
	map->player_coords = (t_vector2){5, 5};
	map->direction = 'N';
	return map;
}

int	main(int ac, char **av)
{
	t_bool		error;
	t_window	*window;
	t_game		game;

	(void)av;
	(void)ac;
	error = SUCCESS;
	//if (ac != 2)
	//	return (print_error("Usage : ./cube3d [map.ber]"));
	window = mlxe_init(1920 / 2, 1080 / 2, "cube3d");
	if (!window)
		return (print_error("Failed to initialize window"));
	game_init(&game, window, test_map());
	mlxe_loop(window, main_loop, &game);

	//error = FAILURE;
	//set_error(&game, "Test error");

	mlxe_destroy(window);
	if (!error)
		return (print_error(game.error_msg));
	return (0);
}
