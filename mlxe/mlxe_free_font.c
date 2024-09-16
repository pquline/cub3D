/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_free_font.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:42:17 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 00:42:17 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

void	mlxe_free_font(t_window *window, void *font)
{
	t_font	*f;

	f = (t_font *)font;
	if (!f)
		return ;
	if (f->texture)
		mlxe_free_texture(window, f->texture);
	free(f);
}
