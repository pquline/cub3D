/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_add_garbage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:01:49 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 15:57:48 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

t_bool	mlxe_add_garbage(t_window *window,
			void *ptr, void (*ft_free)(t_window *, void *))
{
	t_garbage	*g;
	t_list		*new;

	g = malloc(sizeof(t_garbage));
	if (!g)
	{
		window->error = MLXE_ERROR_MALLOC;
		return (FALSE);
	}
	g->ptr = ptr;
	g->free = ft_free;
	new = ft_lstnew(g);
	if (!new)
	{
		window->error = MLXE_ERROR_MALLOC;
		free(g);
		return (FALSE);
	}
	ft_lstadd_back(&window->garbage, new);
	return (TRUE);
}
