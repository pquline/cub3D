/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 15:07:06 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <stdio.h>

void	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->walls[0] = mlxe_load_texture(window, map->no, TRUE);
	engine->walls[1] = mlxe_load_texture(window, map->ea, TRUE);
	engine->walls[2] = mlxe_load_texture(window, map->so, TRUE);
	engine->walls[3] = mlxe_load_texture(window, map->we, TRUE);
	if (!engine->walls[0] || !engine->walls[1] || !engine->walls[2] || !engine->walls[3])
	{
		printf("Failed to load textures\n");//TODO: handle error
		return ;
	}
	engine->window = window;
	engine->map = map;
	engine->camera.x = map->start_coords.x + 0.5;
	engine->camera.y = map->start_coords.y + 0.5;
	if (map->start_direction == 'E')
		engine->camera.dir = 0;
	else if (map->start_direction == 'S')
		engine->camera.dir = M_PI_2;
	else if (map->start_direction == 'W')
		engine->camera.dir = M_PI;
	else if (map->start_direction == 'N')
		engine->camera.dir = 3 * M_PI_2;
	engine->camera.fov = M_PI / 3;
	engine->entities = NULL;
}

static void	clear_screen(t_window *window, t_color top, t_color bottom)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->buffer->size.y/2)
	{
		j = 0;
		while (j < window->buffer->size.x)
		{
			mlxe_write_pixel(window->buffer, j, i, top);
			mlxe_write_pixel(window->buffer, j, window->buffer->size.y - i - 1, bottom);
			j++;
		}
		i++;
	}
}

void	render_engine(t_engine *engine)
{
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	//draw_entities(engine);
}
