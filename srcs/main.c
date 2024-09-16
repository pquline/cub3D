/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:19 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/16 14:47:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	print_error(char *msg)
{
	ft_putendl_fd("Error : ", 2);
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
	t_bool		error;
	t_window	*window;
	t_game		game;

	(void)ac;
	(void)av;
	error = SUCCESS;
	if (ac != 2)
		return (print_error("Usage : ./cube3d [map.ber]"));
	window = mlxe_init(1920 / 2, 1080 / 2, "cube3d");
	if (!window)
		return (print_error("Failed to initialize window"));
	ft_memset(&game, 0, sizeof(t_game));
	game.window = window;

	error = FAILURE;
	set_error(&game, "Test error");

	mlxe_destroy(window);
	if (!error)
		return (print_error(game.error_msg));
	return (0);
}
