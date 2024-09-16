/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:27:42 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:46:13 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static char	*ft_split_next(char const *s, char c)
{
	while (*s != '\0' && *s != c)
		s++;
	return ((char *)s);
}

static char	**ft_split_malloc(char *s, char c, int *count)
{
	char	*last;

	if (s == NULL)
		return (NULL);
	*count = 0;
	last = s;
	while (*s != '\0')
	{
		s = ft_split_next(s, c);
		if (last < s)
			*count += 1;
		if (*s != '\0')
			s++;
		last = s;
	}
	return ((char **)malloc((*count + 1) * sizeof(char *)));
}

static int	ft_split_line(char const *s, char c, char **res)
{
	int	len;

	len = ft_split_next(s, c) - s;
	*res = (char *)malloc(len + 1);
	if (!(*res))
		return (0);
	(*res)[len] = '\0';
	while (len--)
		(*res)[len] = *(s + len);
	return (1);
}

static char	**ft_split_destroy(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != NULL)
		free(res[i++]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		count;
	char	*last;
	int		idx;

	res = ft_split_malloc((char *)s, c, &count);
	if (!res)
		return (NULL);
	res[count] = NULL;
	last = (char *)s;
	idx = 0;
	while (idx < count)
	{
		s = ft_split_next(s, c);
		if (last < s)
			if (!ft_split_line(last, c, res + idx++))
				return (ft_split_destroy(res));
		if (*s != '\0')
			s++;
		last = (char *)s;
	}
	return (res);
}
