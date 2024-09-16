/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:06:25 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:41:08 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*tab;

	if ((size != 0 && (nmemb > ((unsigned int) -1 / size))))
		return (NULL);
	tab = (unsigned char *)malloc(nmemb * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
		tab[i++] = 0;
	return ((void *)tab);
}
