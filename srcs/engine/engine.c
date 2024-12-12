/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 14:44:45 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <stdio.h>

void	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->window = window;
	engine->map = map;
	engine->camera.x = map->start_coords.x + 0.5;
	engine->camera.y = map->start_coords.y + 0.5;
	if (map->start_direction == 'N')
		engine->camera.dir = 0;
	else if (map->start_direction == 'E')
		engine->camera.dir = M_PI_2;
	else if (map->start_direction == 'S')
		engine->camera.dir = M_PI;
	else if (map->start_direction == 'W')
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

t_ray raycast(t_engine *engine, float angle)
{
    t_ray ray;
    float delta_dist_x, delta_dist_y;
    float side_dist_x, side_dist_y;
    int step_x, step_y;
    int hit = 0;

    ray.dir = angle;
    ray.x = engine->camera.x;
    ray.y = engine->camera.y;

    float ray_dir_x = cos(angle);
    float ray_dir_y = sin(angle);

    int map_x = (int)ray.x;
    int map_y = (int)ray.y;

    delta_dist_x = fabs(1 / ray_dir_x);
    delta_dist_y = fabs(1 / ray_dir_y);

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (ray.x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - ray.x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (ray.y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - ray.y) * delta_dist_y;
    }

    int side; // 0 = vertical, 1 = horizontal
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0; // Mur vertical
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1; // Mur horizontal
        }
        if (engine->map->grid[map_y][map_x].id != EMPTY)
            hit = 1;
    }

    if (side == 0)
    {
        ray.dist = (map_x - ray.x + (1 - step_x) / 2) / ray_dir_x;
        ray.side_hit = (step_x < 0) ? 3 : 1; // 3 = ouest, 1 = est
    }
    else
    {
        ray.dist = (map_y - ray.y + (1 - step_y) / 2) / ray_dir_y;
        ray.side_hit = (step_y < 0) ? 0 : 2; // 0 = nord, 2 = sud
    }

    ray.dist *= cos(ray.dir - engine->camera.dir); // Correction du fisheye
    return ray;
}

void draw_map(t_engine *engine)
{
    float camera_plane = engine->camera.fov / 2.0f;

    for (int i = 0; i < engine->window->buffer->size.x; i++)
    {
        float camera_x = 2 * i / (float)engine->window->buffer->size.x - 1;
        float ray_angle = engine->camera.dir + camera_x * camera_plane;

        t_ray ray = raycast(engine, ray_angle);

        int line_height = (int)(engine->window->buffer->size.y / ray.dist);
        int draw_start = -line_height / 2 + engine->window->buffer->size.y / 2;
        int draw_end = line_height / 2 + engine->window->buffer->size.y / 2;

        int color;
        switch (ray.side_hit)
        {
            case 0: // Nord
                color = mlxe_color(255, 0, 0); // Rouge
                break;
            case 1: // Est
                color = mlxe_color(0, 255, 0); // Vert
                break;
            case 2: // Sud
                color = mlxe_color(0, 0, 255); // Bleu
                break;
            case 3: // Ouest
                color = mlxe_color(255, 255, 0); // Jaune
                break;
        }

        mlxe_draw_line(engine->window,
            (t_vector2){i, draw_start},
            (t_vector2){i, draw_end},
            color);
    }
}


void	render_engine(t_engine *engine)
{
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	//draw_entities(engine);
}
