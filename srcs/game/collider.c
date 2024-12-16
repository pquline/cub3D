/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:14 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 16:22:20 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	want_to_move(t_engine *engine, float x, float y)
{
	if (x < 0 || x >= engine->map->width || y < 0 || y >= engine->map->height)
		return ;
	if (engine->map->grid[(int)y][(int)x].id != EMPTY)
		return ;
	// Taille du carré de collision (0.1)
    float half_size = 0.05;  // La moitié de la taille du carré

    // Vérifier si les coins autour de la position souhaitée sont libres
    for (float dx = -half_size; dx <= half_size; dx += half_size) {
        for (float dy = -half_size; dy <= half_size; dy += half_size) {
            int check_x = (int)(x + dx);
            int check_y = (int)(y + dy);

            // Vérifier les limites du terrain et si la case est occupée
            if (check_x < 0 || check_x >= (int)engine->map->width || check_y < 0 || check_y >= (int)engine->map->height)
                return;  // Si la position est en dehors de la carte, on annule le déplacement

            if (engine->map->grid[check_y][check_x].id != EMPTY)
                return;  // Si la case est occupée, on annule le déplacement
        }
    }

	float mov_dir = atan2(y - engine->camera.y, x - engine->camera.x);
	t_ray ray = raycast(engine, mov_dir);
	float dist = sqrt(pow(engine->camera.x - x, 2) + pow(engine->camera.y - y, 2));
	if (ray.dist < dist)
		return ;
	engine->camera.x = x;
	engine->camera.y = y;
}

void	add_move(t_engine *engine, float x, float y)
{
	want_to_move(engine, engine->camera.x + x, engine->camera.y + y);
}