/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/11 19:01:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <stdio.h>

void	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->window = window;
	engine->map = map;
	engine->camera.x = map->player_coords.x + 0.5;
	engine->camera.y = map->player_coords.y + 0.5;
	if (map->direction == 'N')
		engine->camera.dir = 0;
	else if (map->direction == 'E')
		engine->camera.dir = M_PI_2;
	else if (map->direction == 'S')
		engine->camera.dir = M_PI;
	else if (map->direction == 'W')
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
    int side;

    ray.dir = angle;
    ray.x = engine->camera.x;
    ray.y = engine->camera.y;

    // Calcul des directions initiales
    float ray_dir_x = cos(angle);
    float ray_dir_y = sin(angle);

    int map_x = (int)ray.x;
    int map_y = (int)ray.y;

    delta_dist_x = fabs(1 / ray_dir_x);
    delta_dist_y = fabs(1 / ray_dir_y);

    // Calcul des étapes et distances initiales
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

    // Lancement du DDA
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
        if (engine->map->grid[map_y][map_x] != EMPTY)
            hit = 1;
    }

    // Calcul de la distance perpendiculaire pour réduire le fisheye
    if (side == 0)
        ray.dist = (map_x - ray.x + (1 - step_x) / 2) / ray_dir_x;
    else
        ray.dist = (map_y - ray.y + (1 - step_y) / 2) / ray_dir_y;

    // Correction du fisheye
    ray.dist *= cos(ray.dir - engine->camera.dir);

    ray.x = ray.x + ray.dist * ray_dir_x;
    ray.y = ray.y + ray.dist * ray_dir_y;

    return ray;
}

void draw_map(t_engine *engine)
{
    float camera_plane = engine->camera.fov / 2.0f;
    for (int i = 0; i < engine->window->buffer->size.x; i++)
    {
        // Calcul de l'angle du rayon pour chaque colonne
        float camera_x = 2 * i / (float)engine->window->buffer->size.x - 1;
        float ray_angle = engine->camera.dir + camera_x * camera_plane;

        t_ray ray = raycast(engine, ray_angle);

        // Projection de la hauteur des murs
        int line_height = (int)(engine->window->buffer->size.y / ray.dist);
        int draw_start = -line_height / 2 + engine->window->buffer->size.y / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + engine->window->buffer->size.y / 2;
        if (draw_end >= engine->window->buffer->size.y) draw_end = engine->window->buffer->size.y - 1;

        // Couleur avec effet de distance
        int color = 255 - (ray.dist * 6);
        if (color < 0) color = 0;
        mlxe_draw_line(engine->window,
            (t_vector2){i, draw_start},
            (t_vector2){i, draw_end},
            mlxe_color(color, color, color));
    }
}


void	render_engine(t_engine *engine)
{
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	//draw_entities(engine);
}