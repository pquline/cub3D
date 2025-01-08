/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:53:11 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 11:59:22 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

// Fonction pour calculer la distance entre le joueur et une entité
static float calculate_distance(t_camera *camera, t_entity *entity)
{
    return sqrt(pow(entity->pos[0] - camera->x, 2) + pow(entity->pos[1] - camera->y, 2));
}

// Fonction de tri : tri rapide pour une liste chaînée
static t_list *partition(t_list *head, t_list **low, t_list **high, t_camera *camera)
{
    t_list *pivot = head;
    float pivot_dist = calculate_distance(camera, pivot->content);

    t_list *current = head->next;
    while (current)
    {
        float current_dist = calculate_distance(camera, current->content);
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

static t_list *quick_sort(t_list *head, t_camera *camera)
{
    if (!head || !head->next)
        return head;

    t_list *low = NULL;
    t_list *high = NULL;

    t_list *pivot = partition(head, &low, &high, camera);

    low = quick_sort(low, camera);
    high = quick_sort(high, camera);

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

void draw_entities(t_engine *engine)
{
	engine->entities = quick_sort(engine->entities, &engine->camera);
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
			draw_subtexture_size_z(engine, entity->sprites->texture,
                                      (t_coords){entity->sprites->rect, rect}, corrected_dist);

        }

        entities = entities->next;
    }
}
