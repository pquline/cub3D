/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:20:14 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/18 15:33:47 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_bool	check_collider_block(t_tile *tile)
{
	if (tile->id == EMPTY)
		return (SUCCESS);
	if (tile->id == DOOR_HOR || tile->id == DOOR_VER)
	{
		if (tile->data > 0)
			return (SUCCESS);
	}
	return (FAILURE);
}

t_bool	want_to_move(t_entity *entity, float x, float y)
{
	t_engine *engine = &entity->game->engine;

	if (x < 0 || x >= engine->map->width || y < 0 || y >= engine->map->height)
		return (FAILURE);
	if (check_collider_block(&engine->map->grid[(int)y][(int)x]) == FAILURE)
		return (FAILURE);
	// Taille du carré de collision (0.1)
    float half_size = 0.05;  // La moitié de la taille du carré

    // Vérifier si les coins autour de la position souhaitée sont libres
    for (float dx = -half_size; dx <= half_size; dx += half_size) {
        for (float dy = -half_size; dy <= half_size; dy += half_size) {
            int check_x = (int)(x + dx);
            int check_y = (int)(y + dy);

            // Vérifier les limites du terrain et si la case est occupée
            if (check_x < 0 || check_x >= (int)engine->map->width || check_y < 0 || check_y >= (int)engine->map->height)
                return (FAILURE);  // Si la position est en dehors de la carte, on annule le déplacement

			if (check_collider_block(&engine->map->grid[check_y][check_x]) == FAILURE)
                return (FAILURE);  // Si la case est occupée, on annule le déplacement
        }
    }

	float mov_dir = atan2(y - entity->pos[1], x - entity->pos[0]);
	t_ray ray = raycast(engine, mov_dir);
	float dist = sqrt(pow(entity->pos[0] - x, 2) + pow(entity->pos[1] - y, 2));
	if (ray.hit && ray.dist < dist)
	{
		if (check_collider_block(&engine->map->grid[(int)ray.y][(int)ray.x]) == FAILURE)
			return (FAILURE);
	}
	entity->pos[0] = x;
	entity->pos[1] = y;
	entity->mov_dir = mov_dir;
	return (SUCCESS);
}

t_bool	add_move(t_entity *entity, float x, float y)
{
	return want_to_move(entity, entity->pos[0] + x, entity->pos[1] + y);
}