/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:49:50 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/07 18:10:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <cub3D.h>
#include <stdio.h>

t_bool	engine_init(t_engine *engine, t_window *window, t_map *map)
{
	engine->game = NULL;
	engine->window = window;
	engine->z_buffer = malloc(sizeof(float) * window->buffer->size.x);
	if (!engine->z_buffer)
		return (FAILURE);
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
	engine->camera.fov = M_PI / 2.8;
	engine->entities = NULL;
	ft_memset(engine->render_block, 0, sizeof(engine->render_block));
	return (SUCCESS);
}

void	destory_engine(t_engine *engine)
{
	free(engine->z_buffer);
	ft_lstclear(&engine->entities, free);
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







// Fonction pour calculer la distance entre le joueur et une entité
float calculate_distance(t_entity *player, t_entity *entity)
{
    return sqrt(pow(entity->pos[0] - player->pos[0], 2) + pow(entity->pos[1] - player->pos[1], 2));
}

// Fonction de tri : tri rapide pour une liste chaînée
t_list *partition(t_list *head, t_list **low, t_list **high, t_entity *player)
{
    t_list *pivot = head;
    float pivot_dist = calculate_distance(player, pivot->content);

    t_list *current = head->next;
    while (current)
    {
        float current_dist = calculate_distance(player, current->content);
        if (current_dist > pivot_dist)
        {
            t_list *next = current->next;
            current->next = *low;
            *low = current;
            current = next;
        }
        else
        {
            t_list *next = current->next;
            current->next = *high;
            *high = current;
            current = next;
        }
    }

    return pivot;
}

t_list *quick_sort(t_list *head, t_entity *player)
{
    if (!head || !head->next)
        return head;

    t_list *low = NULL;
    t_list *high = NULL;

    t_list *pivot = partition(head, &low, &high, player);

    low = quick_sort(low, player);
    high = quick_sort(high, player);

    // Fusionner les trois parties
    t_list *sorted = low;

    // Ajouter la partie pivotée au tri bas
    if (sorted)
    {
        t_list *tail = sorted;
        while (tail->next)
            tail = tail->next;
        tail->next = pivot;
    }
    else
    {
        sorted = pivot;
    }

    // Ajouter la partie triée haute au pivot
    pivot->next = high;

    return sorted;
}

// Fonction principale pour trier les entités
void sort_entities(t_list **entities, t_entity *player)
{
    *entities = quick_sort(*entities, player);
}


#include <sp_mlxe.h>

void draw_entities(t_engine *engine)
{
	sort_entities(&engine->entities, ((t_game*)engine->game)->player);
    t_list *entities = engine->entities;

    while (entities)
    {
        t_entity *entity = entities->content;
        if (entity->sprites == NULL)
        {
            entities = entities->next;
            continue;
        }

        // Position de l'entité relative à la caméra
        float dx = entity->pos[0] - engine->camera.x;
        float dy = entity->pos[1] - engine->camera.y;

        // Calcul de la distance et de l'angle par rapport à la caméra
        float dist = sqrt(dx * dx + dy * dy);
        float angle = atan2(dy, dx);
        float diff = angle - engine->camera.dir;

        // Normalisation de l'angle dans [-PI, PI]
        while (diff > M_PI)
            diff -= 2 * M_PI;
        while (diff < -M_PI)
            diff += 2 * M_PI;

        // Vérification si l'entité est visible (dans le champ de vision)
        if (fabs(diff) < engine->camera.fov / 2)
        {
            // Correction de la distance pour éliminer la distorsion (fisheye)
            float corrected_dist = dist * cos(diff);

            // Calcul de la position horizontale (screen_x) alignée avec le raycasting
            int screen_x = (int)((engine->window->buffer->size.x / 2) *
                                 (1 + tan(diff) / tan(engine->camera.fov / 2)));

            // Calcul de la hauteur projetée
            int line_height = (int)(engine->window->buffer->size.y / corrected_dist);

            // Calcul de la position verticale (centrée)
            int screen_y = engine->window->buffer->size.y / 2 - line_height / 2;

            // Définir la taille et la position du sprite
            t_rect rect = {screen_x - line_height / 2, screen_y, line_height, line_height};

            // Dessiner l'entité
			draw_subtexture_size_z(engine->window, entity->sprites->texture,
                                      (t_coords){entity->sprites->rect, rect},engine->z_buffer, corrected_dist);

        }

        entities = entities->next;
    }
}













void	render_engine(t_engine *engine)
{
	ft_memset(engine->z_buffer, 0, sizeof(float) * engine->window->buffer->size.x);
	clear_screen(engine->window, engine->map->c, engine->map->f);
	draw_map(engine);
	draw_entities(engine);
}
