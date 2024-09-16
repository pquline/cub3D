/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:40:07 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/16 14:42:47 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstremove(t_list **lst, void *elem, void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	prev = NULL;
	while (curr)
	{
		if (curr->content == elem)
		{
			if (prev)
				prev->next = curr->next;
			else
				*lst = curr->next;
			if (del)
				del(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
