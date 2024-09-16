/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:27:52 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:38:57 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	lstr;

	lstr = ft_strlen(s);
	if (start >= lstr)
		len = 0;
	else if (start + len > lstr)
		len = lstr - start;
	if (len > lstr)
		len = lstr;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if (start < lstr)
		ft_strlcpy(res, s + start, len + 1);
	res[len] = '\0';
	return (res);
}
