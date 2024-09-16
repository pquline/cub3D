/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:19:58 by lfarhi            #+#    #+#             */
/*   Updated: 2024/05/29 15:13:25 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	gnl_strstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != '\n' && str[i] != 13)
		i++;
	return (i);
}

void	gnl_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	gnl_strcat_realloc(char **src, char *add)
{
	char	*new;
	size_t	len_src;
	size_t	len_add;

	len_src = gnl_strlen(*src);
	len_add = gnl_strlen(add);
	if (add && add[len_add] == '\n')
		len_add++;
	if (*src && len_add == 0)
		return (1);
	new = malloc(len_src + len_add + 1);
	if (new == NULL)
		return (0);
	gnl_memcpy(new, *src, len_src);
	gnl_memcpy(new + len_src, add, len_add);
	new[len_src + len_add] = '\0';
	free(*src);
	*src = new;
	return (1);
}
