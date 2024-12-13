/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:14:13 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/13 14:11:26 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*parsing_error(char *error)
{
	ft_putendl_fd("Error:", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (NULL);
}
