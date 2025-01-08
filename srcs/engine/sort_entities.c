/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:22:25 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:48:35 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <math.h>

static float	calculate_distance(t_camera *camera, t_entity *entity)
{
	return (sqrt(pow(entity->pos[0] - camera->x, 2)
			+ pow(entity->pos[1] - camera->y, 2)));
}

static t_list	*partition(t_list *head, t_list **low,
	t_list **high, t_camera *camera)
{
	t_list	*pivot;
	t_list	*current;
	t_list	*next;
	float	dist[2];

	pivot = head;
	dist[0] = calculate_distance(camera, pivot->content);
	current = head->next;
	while (current)
	{
		dist[1] = calculate_distance(camera, current->content);
		next = current->next;
		if (dist[1] >= dist[0])
		{
			current->next = *low;
			*low = current;
		}
		else
		{
			current->next = *high;
			*high = current;
		}
		current = next;
	}
	return (pivot);
}

t_list	*quick_sort_render(t_list *head, t_camera *camera)
{
	t_list	*low;
	t_list	*high;
	t_list	*pivot;
	t_list	*sorted;
	t_list	*tail;

	if (!head || !head->next)
		return (head);
	low = NULL;
	high = NULL;
	pivot = partition(head, &low, &high, camera);
	low = quick_sort_render(low, camera);
	high = quick_sort_render(high, camera);
	sorted = low;
	if (sorted)
	{
		tail = sorted;
		while (tail->next)
			tail = tail->next;
		tail->next = pivot;
	}
	else
		sorted = pivot;
	pivot->next = high;
	return (sorted);
}
