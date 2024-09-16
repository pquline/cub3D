/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_free_garbage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:02:46 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 17:13:45 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static void	clear_garbage(t_window *window, void *ptr)
{
	t_garbage	*g;

	g = (t_garbage *)ptr;
	if (g->free)
		g->free(window, g->ptr);
	free(g);
}

void	mlxe_free(t_window *window, void *ptr)
{
	(void)window;
	free(ptr);
}

void	mlxe_free_garbage(t_window *window)
{
	t_list	*tmp;
	t_list	*next;

	tmp = window->garbage;
	while (tmp)
	{
		next = tmp->next;
		clear_garbage(window, tmp->content);
		free(tmp);
		tmp = next;
	}
	window->garbage = NULL;
}
