/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:32 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 16:31:41 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>


void	main_loop(t_window *window, void *data)
{
	t_game	*game;
	t_time	start;
	t_time	end;
	float	speed_move;
	float	speed_mouse;

	game = (t_game *)data;
	speed_move = adaptive_speed(0.003, game->delta_time);
	speed_mouse = adaptive_speed(0.0003, game->delta_time);
	//move forward
	if (mlxe_is_key_pressed(window, XK_w))
		add_move(&game->engine, cos(game->engine.camera.dir) * speed_move, sin(game->engine.camera.dir) * speed_move);
	//move backward
	if (mlxe_is_key_pressed(window, XK_s))
		add_move(&game->engine, -cos(game->engine.camera.dir) * speed_move, -sin(game->engine.camera.dir) * speed_move);
	//strafe right
	if (mlxe_is_key_pressed(window, XK_d))
		add_move(&game->engine, cos(game->engine.camera.dir + M_PI_2) * speed_move, sin(game->engine.camera.dir + M_PI_2) * speed_move);
	//strafe left
	if (mlxe_is_key_pressed(window, XK_a))
		add_move(&game->engine, cos(game->engine.camera.dir - M_PI_2) * speed_move, sin(game->engine.camera.dir - M_PI_2) * speed_move);
	game->engine.camera.dir -= (window->width / 2 - window->mouse.x) * speed_mouse;
	if (mlxe_is_key_pressed(window, XK_Left))
		game->engine.camera.dir -= speed_move;
	if (mlxe_is_key_pressed(window, XK_Right))
		game->engine.camera.dir += speed_move;
	
	start = get_time();
	render_engine(&game->engine);
	draw_minimap(game);
	mlxe_render(window);
	mlxe_mouse_move(window, window->width / 2, 1000000);
	end = get_time();
	game->delta_time = get_delta(start, end);
}

t_bool	game_init(t_game *game, t_window *window, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window = window;
	if (!load_assets(&game->assets, window))
		return (FAILURE);
	engine_init(&game->engine, window, map);
	return (SUCCESS);
}
