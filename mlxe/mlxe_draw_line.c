/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_draw_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:24:21 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 00:24:21 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static t_bool	calcule_t(float *t, const float *p, const float *q, int i)
{
	float	r;

	if (p[i] == 0 && q[i] < 0)
		return (FALSE);
	r = q[i] / p[i];
	if (p[i] < 0)
	{
		if (r > t[1])
			return (FALSE);
		else if (r > t[0])
			t[0] = r;
	}
	else if (p[i] > 0)
	{
		if (r < t[0])
			return (FALSE);
		else if (r < t[1])
			t[1] = r;
	}
	return (TRUE);
}

void	clip_line(t_vector2 *p1, t_vector2 *p2, int width, int height)
{
	const float	delta[2] = {p2->x - p1->x, p2->y - p1->y};
	const float	p[] = {-delta[0], delta[0], -delta[1], delta[1]};
	const float	q[] = {p1->x, width - 1 - p1->x, p1->y, height - 1 - p1->y};
	float		t[2];
	int			i;

	t[0] = 0.0f;
	t[1] = 1.0f;
	i = 0;
	while (i < 4)
	{
		if (!calcule_t(t, p, q, i))
			return ;
		i++;
	}
	p2->x = p1->x + t[1] * delta[0];
	p2->y = p1->y + t[1] * delta[1];
	p1->x = p1->x + t[0] * delta[0];
	p1->y = p1->y + t[0] * delta[1];
}

static t_vector2	init(t_vector2 *delta,
	t_vector2 *sign, t_vector2 p1, t_vector2 p2)
{
	if (p1.x < p2.x)
		delta->x = p2.x - p1.x;
	else
		delta->x = p1.x - p2.x;
	if (p1.y < p2.y)
		delta->y = p2.y - p1.y;
	else
		delta->y = p1.y - p2.y;
	if (p1.x < p2.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (p1.y < p2.y)
		sign->y = 1;
	else
		sign->y = -1;
	return (p1);
}

void	mlxe_draw_line(t_window *window,
	t_vector2 p1, t_vector2 p2, t_color color)
{
	t_vector2	delta;
	t_vector2	sign;
	t_vector2	error;
	t_vector2	current;

	clip_line(&p1, &p2, window->buffer->size.x, window->buffer->size.y);
	current = init(&delta, &sign, p1, p2);
	error.x = delta.x - delta.y;
	while (current.x != p2.x || current.y != p2.y)
	{
		mlxe_write_pixel(window->buffer, current.x, current.y, color);
		if (current.x == p2.x && current.y == p2.y)
			break ;
		error.y = error.x * 2;
		if (error.y > -delta.y)
		{
			error.x -= delta.y;
			current.x += sign.x;
		}
		if (error.y < delta.x)
		{
			error.x += delta.x;
			current.y += sign.y;
		}
	}
}
