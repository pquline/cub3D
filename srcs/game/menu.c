/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 14:25:53 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	menu_text(t_game *game, float i, t_window *window, t_color c)
{
	t_vector2	size;

	mlxe_font_set_color(game->assets.main_font, c);
	mlxe_font_set_size(game->assets.main_font, 140);
	size = get_text_size(game->assets.main_font, "PACASTING");
	mlxe_draw_text(window, game->assets.main_font,
		"PACASTING", (t_vector2){window->width / 2 - size.x / 2,
		window->height / 6 - size.y / 2});
	mlxe_font_set_size(game->assets.main_font, 64);
	size = get_text_size(game->assets.main_font, "MOVE TO START");
	mlxe_draw_text(window, game->assets.main_font, "MOVE TO START",
		(t_vector2){window->width / 2 - size.x / 2,
		(window->height / 6.0f) * 4 - size.y / 2 + cos(i) * 10});
}

void	main_menu_loop(t_window *window, void *data)
{
	static float	i = 0;
	t_color			c;
	t_rgb			crgb;
	t_game			*game;

	game = (t_game *)data;
	render_engine(&game->engine);
	c = (game->engine.map->c + game->engine.map->f) / 2;
	crgb = mlxe_extract_rgb(c);
	c = mlxe_color(255 - crgb.r, 255 - crgb.g, 255 - crgb.b);
	menu_text(game, i, window, c);
	i = fmod(i + 0.06, 2 * 3.14159f);
	if (mlxe_is_key_down(window, XK_w) || mlxe_is_key_down(window, XK_a)
		|| mlxe_is_key_down(window, XK_s) || mlxe_is_key_down(window, XK_d))
	{
		window->funct_ptr = main_loop;
		mlxe_mouse_move(window, window->width / 2, window->height);
	}
	mlxe_render(window);
}

void	pause_menu_loop(t_window *window, void *data)
{
	t_game		*game;
	t_vector2	size;

	game = (t_game *)data;
	render_engine(&game->engine);
	mlxe_font_set_color(game->assets.main_font, mlxe_color(255, 255, 255));
	mlxe_font_set_size(game->assets.main_font, 160);
	size = get_text_size(game->assets.main_font,
			"PAUSE");
	mlxe_draw_text(window, game->assets.main_font, "PAUSE",
		(t_vector2){window->width / 2 - size.x / 2,
		window->height / 2 - size.y / 2});
	if (mlxe_is_key_down(window, XK_Tab))
	{
		window->funct_ptr = main_loop;
		mlxe_mouse_move(window, window->width / 2, window->height);
	}
	mlxe_render(window);
}

void	gameover_loop(t_window *window, void *data)
{
	(void)window;
	(void)data;
}
