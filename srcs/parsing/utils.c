/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:59 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 15:51:35 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_strlen_safe(const char *string)
{
	size_t	index;

	index = 0;
	while (string && string[index])
		++index;
	return (index);
}

char	*ft_strjoin_safe(char const *s1, char const *s2)
{
	size_t	len1;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	len1 = ft_strlen_safe(s1);
	res = (char *)malloc(len1 + ft_strlen_safe(s2) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, -1);
	ft_strlcpy(res + len1, s2, -1);
	return (res);
}

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
