/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:53:11 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:28:02 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <math.h>

static void	init_draw_entity(t_engine *engine,
	t_entity *entity, float *dist, float *diff)
{
	float	dx;
	float	dy;
	float	angle;

	dx = entity->pos[0] - engine->camera.x;
	dy = entity->pos[1] - engine->camera.y;
	*dist = sqrt(dx * dx + dy * dy);
	angle = atan2(dy, dx);
	*diff = angle - engine->camera.dir;
	while (*diff > M_PI)
		*diff -= 2 * M_PI;
	while (*diff < -M_PI)
		*diff += 2 * M_PI;
}

static t_rect	get_rect(t_engine *engine,
	float corrected_dist, float diff)
{
	int		screen_x;
	int		line_height;
	int		screen_y;
	t_rect	rect;

	screen_x = (int)((engine->window->buffer->size.x / 2)
			* (1 + tan(diff) / tan(engine->camera.fov / 2)));
	line_height = (int)(engine->window->buffer->size.y / corrected_dist);
	screen_y = engine->window->buffer->size.y / 2 - line_height / 2;
	rect = (t_rect){screen_x - line_height / 2, screen_y,
		line_height, line_height};
	return (rect);
}

void	draw_entities(t_engine *engine)
{
	t_list		*entities;
	t_entity	*entity;
	float		dist;
	float		diff;
	float		corrected_dist;

	engine->entities = quick_sort_render(engine->entities, &engine->camera);
	entities = engine->entities;
	while (entities)
	{
		entity = (t_entity *)entities->content;
		if (entity->sprites != NULL)
		{
			init_draw_entity(engine, entity, &dist, &diff);
			if (fabs(diff) < engine->camera.fov / 2)
			{
				corrected_dist = dist * cos(diff);
				draw_subtexture_size_z(engine, entity->sprites->texture,
					(t_coords){entity->sprites->rect, get_rect(engine,
						corrected_dist, diff)}, corrected_dist);
			}
		}
		entities = entities->next;
	}
}
