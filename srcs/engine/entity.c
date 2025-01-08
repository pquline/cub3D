/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:00:37 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 15:41:35 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_entity	*spawn_entity(t_engine *engine, void *game,
	t_efunc efunc, t_sprite *sprites)
{
	t_entity	*entity;
	t_list		*new;

	entity = malloc(sizeof(t_entity));
	if (!entity)
		return (NULL);
	entity->game = game;
	entity->pos[0] = 0;
	entity->pos[1] = 0;
	entity->dir = 0;
	entity->mov_dir = 0;
	entity->efunc = efunc;
	entity->anim = 0;
	entity->anim_map = 0;
	entity->sprites = sprites;
	entity->data = (NULL);
	new = ft_lstnew(entity);
	if (!new)
	{
		free(entity);
		return (NULL);
	}
	ft_lstadd_back(&engine->entities, new);
	return (entity);
}

void	set_entity_pos(t_entity *entity, float x, float y)
{
	entity->pos[0] = x;
	entity->pos[1] = y;
}

void	free_entity(void *entity)
{
	t_entity	*e;

	e = (t_entity *)entity;
	if (e->data && e->efunc.free_data)
		e->efunc.free_data(e->data);
	free(e);
}

void	delete_entity(t_engine *engine, t_entity *entity)
{
	t_list	*current;

	current = engine->entities;
	while (current)
	{
		if (current->content == entity)
		{
			free_entity(current->content);
			current->content = NULL;
			return ;
		}
		current = current->next;
	}
}

void	remove_empty_entities(t_engine *engine)
{
	t_list	*curr;
	t_list	*prev;

	curr = engine->entities;
	prev = NULL;
	while (curr)
	{
		if (curr->content == NULL)
		{
			if (prev)
				prev->next = curr->next;
			else
				engine->entities = curr->next;
		}
		prev = curr;
		curr = curr->next;
	}
}
