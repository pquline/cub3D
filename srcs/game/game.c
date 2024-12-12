/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:32 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 14:43:38 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void want_to_move(t_engine *engine, float x, float y)
{
	if (x < 0 || x >= engine->map->width || y < 0 || y >= engine->map->height)
		return ;
	if (engine->map->grid[(int)y][(int)x].id != EMPTY)
		return ;
	engine->camera.x = x;
	engine->camera.y = y;
}

void add_move(t_engine *engine, float x, float y)
{
	want_to_move(engine, engine->camera.x + x, engine->camera.y + y);
}

void draw_minimap(t_game *game)
{
	size_t		y;
	size_t		x;
	t_camera	*camera;

	camera = &game->engine.camera;
	y = 0;
	while (y < game->engine.map->height)
	{
		x = 0;
		while (x < game->engine.map->width)
		{
			if (game->engine.map->grid[y][x].id == WALL)
				mlxe_draw_fillrect(game->window, (t_rect){x * 10, y * 10, 10, 10}, mlxe_color(0, 0, 255));
			x++;
		}
		y++;
	}
	mlxe_draw_fillrect(game->window, (t_rect){(camera->x * 10) - 2, (camera->y * 10) - 2, 4, 4}, mlxe_color(255, 0, 0));
	mlxe_draw_line(game->window, (t_vector2){camera->x * 10, camera->y * 10}, (t_vector2){camera->x * 10 + 10 * cos(camera->dir), camera->y * 10 + 10 * sin(camera->dir)}, mlxe_color(255, 0, 0));
}

void	main_loop(t_window *window, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	//move forward
	if (mlxe_is_key_pressed(window, XK_w))
		add_move(&game->engine, cos(game->engine.camera.dir) * 0.01, sin(game->engine.camera.dir) * 0.01);
	//move backward
	if (mlxe_is_key_pressed(window, XK_s))
		add_move(&game->engine, -cos(game->engine.camera.dir) * 0.01, -sin(game->engine.camera.dir) * 0.01);
	//strafe right
	if (mlxe_is_key_pressed(window, XK_d))
		add_move(&game->engine, cos(game->engine.camera.dir + M_PI_2) * 0.01, sin(game->engine.camera.dir + M_PI_2) * 0.01);
	//strafe left
	if (mlxe_is_key_pressed(window, XK_a))
		add_move(&game->engine, cos(game->engine.camera.dir - M_PI_2) * 0.01, sin(game->engine.camera.dir - M_PI_2) * 0.01);
	if (mlxe_is_key_pressed(window, XK_Left))
		game->engine.camera.dir -= 0.01;
	if (mlxe_is_key_pressed(window, XK_Right))
		game->engine.camera.dir += 0.01;

	render_engine(&game->engine);
	draw_minimap(game);
	mlxe_render(window);
}
