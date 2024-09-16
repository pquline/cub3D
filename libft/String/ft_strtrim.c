/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:27:51 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:39:03 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strtrim_is_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static	void	ft_strtrim_delimit(char *s1, char *set, char **st, char **end)
{
	*st = s1;
	*end = s1 + ft_strlen(s1) - 1;
	while (ft_strtrim_is_set(**st, set) && *st <= *end)
		*st += 1;
	while (ft_strtrim_is_set(**end, set) && *st <= *end)
		*end -= 1;
	*end += 1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*st;
	char	*end;
	char	*res;

	ft_strtrim_delimit((char *)s1, (char *)set, &st, &end);
	res = (char *)malloc(end - st + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, st, end - st + 1);
	return (res);
}
