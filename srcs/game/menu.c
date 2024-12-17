/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 19:08:58 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	main_menu_loop(t_window *window, void *data)
{
	t_game	*game;
	game = (t_game *)data;
	render_engine(&game->engine);
	mlxe_render(window);
}

void	pause_menu_loop(t_window *window, void *data)
{
	t_game	*game;
	game = (t_game *)data;
	render_engine(&game->engine);
	mlxe_font_set_color(game->assets.main_font, mlxe_color(255, 255, 255));
	mlxe_font_set_size(game->assets.main_font, 160);
	t_vector2 size = get_text_size(game->assets.main_font, "PAUSE");
	mlxe_draw_text(window, game->assets.main_font, "PAUSE", (t_vector2){window->width / 2 - size.x / 2, window->height / 2 - size.y / 2});
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