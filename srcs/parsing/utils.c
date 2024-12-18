/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:59 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/18 09:48:42 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

char	*ft_strndup(const char *string, size_t size)
{
	size_t	index;
	char	*dup;

	if (string == NULL || string[0] == 0)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (size + sizeof(char)));
	if (dup == NULL)
		return (NULL);
	index = 0;
	while (index < size && string[index] != 0)
	{
		dup[index] = string[index];
		index++;
	}
	dup[index] = 0;
	return (dup);
}
