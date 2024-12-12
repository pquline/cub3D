/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 17:44:35 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <stdio.h>

void	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->walls[0] = mlxe_load_texture(window, map->no, TRUE);
	engine->walls[1] = mlxe_load_texture(window, map->so, TRUE);
	engine->walls[2] = mlxe_load_texture(window, map->we, TRUE);
	engine->walls[3] = mlxe_load_texture(window, map->ea, TRUE);
	if (!engine->walls[0] || !engine->walls[1] || !engine->walls[2] || !engine->walls[3])
	{
		printf("Failed to load textures\n");
		return ;
	}
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

    // Calcul des delta_dist pour chaque pas
    delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

    // Détermination des directions de progression et des distances initiales
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

    // Calcul de la distance en fonction du côté touché
    if (side == 0)
    {
        ray.dist = (map_x - ray.x + (1 - step_x) / 2.0) / ray_dir_x;
        ray.side_hit = (step_x < 0) ? 3 : 1; // 3 = ouest, 1 = est
        ray.x_t = ray.y + ray.dist * ray_dir_y - floor(ray.y + ray.dist * ray_dir_y);
    }
    else
    {
        ray.dist = (map_y - ray.y + (1 - step_y) / 2.0) / ray_dir_y;
        ray.side_hit = (step_y < 0) ? 0 : 2; // 0 = nord, 2 = sud
        ray.x_t = ray.x + ray.dist * ray_dir_x - floor(ray.x + ray.dist * ray_dir_x);
    }
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

        // Appliquer une correction de fisheye sur la distance
        ray.dist *= cos(ray.dir - engine->camera.dir);

        // Calcul de la hauteur de la ligne
        int line_height = (int)(engine->window->buffer->size.y / fmax(ray.dist, 0.1f)); // Eviter les distorsions extrêmes
        int draw_start = -line_height / 2 + engine->window->buffer->size.y / 2;
        int draw_end = line_height / 2 + engine->window->buffer->size.y / 2;

        if (draw_start < 0) draw_start = 0;
        if (draw_end >= engine->window->buffer->size.y) draw_end = engine->window->buffer->size.y - 1;

        int side_dir = ray.side_hit; // Nord, Sud, Est, Ouest
        int texture_width = engine->walls[side_dir]->size.x;
        int texture_height = engine->walls[side_dir]->size.y;

        // Calculer la coordonnée x dans la texture
        int tex_x = (int)(ray.x_t * texture_width);
		
        tex_x = tex_x % texture_width;  // Assure-toi que tex_x est toujours dans les limites de la texture

        // Dessin de chaque ligne de pixel
        for (int y = draw_start; y < draw_end; y++)
        {
            int d = y * 256 - engine->window->buffer->size.y * 128 + line_height * 128;
            int tex_y = ((d * texture_height) / line_height) / 256;

            t_color color = mlxe_get_pixel(engine->walls[side_dir], tex_x, tex_y);
            mlxe_draw_pixel(engine->window->buffer, i, y, color);
        }
    }
}

void	render_engine(t_engine *engine)
{
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	//draw_entities(engine);
}
