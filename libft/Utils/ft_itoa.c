/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:27:31 by lfarhi            #+#    #+#             */
/*   Updated: 2024/09/12 14:46:10 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*malloc_itoa(int n, int *len)
{
	*len = n <= 0;
	while (n != 0)
	{
		n /= 10;
		(*len)++;
	}
	return ((char *)malloc(*len + 1));
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;

	res = malloc_itoa(n, &len);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	else if (n < 0)
	{
		res[0] = '-';
		res[--len] = ((-(long long)n) % 10) + '0';
		n = -(n / 10);
	}
	while (len-- && n != 0)
	{
		res[len] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
