/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:01:37 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:39:33 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	head;
	t_list	*new_temp;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	head.next = NULL;
	new_temp = &head;
	while (lst)
	{
		new_content = f(lst->content);
		new_temp->next = ft_lstnew(new_content);
		if (!new_temp->next)
		{
			if (new_content && del)
				del(new_content);
			ft_lstclear(&head.next, del);
			return (NULL);
		}
		new_temp = new_temp->next;
		lst = lst->next;
	}
	return (head.next);
}
