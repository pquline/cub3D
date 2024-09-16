/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:07:40 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:39:17 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dlen;
	unsigned int	slen;

	dlen = 0;
	while (dlen < size && dst[dlen] != '\0')
		dlen++;
	dst += dlen;
	if (dlen == size)
		return (dlen + ft_strlen(src));
	size = size - dlen;
	slen = 0;
	while (src[slen] != '\0')
	{
		if (size != 1)
		{
			*dst++ = src[slen];
			size--;
		}
		slen++;
	}
	*dst = '\0';
	return (dlen + slen);
}
