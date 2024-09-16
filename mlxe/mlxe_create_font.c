/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_create_font.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:26:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 00:26:39 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

static int	get_char_width(t_texture *txt, int start)
{
	int		width;
	int		i;
	t_color	alpha;

	width = (mlxe_read_pixel(txt, start, 0) & 0xFF000000) == 0;
	i = start + width;
	while (i < txt->size.x)
	{
		alpha = mlxe_read_pixel(txt, i, 0) & 0xFF000000;
		if (!alpha)
			return (width);
		width++;
		i++;
	}
	return (width);
}

static void	save_all_width(t_font *font)
{
	int		i;
	int		width;

	i = 0;
	width = 0;
	while (i < 127 - 32)
	{
		font->widths[i][0] = get_char_width(font->texture, width);
		font->widths[i][1] = width;
		width += font->widths[i][0];
		i++;
	}
}

static t_font	*exit_free(t_window *window,
	t_font *font, int error)
{
	window->error = error;
	if (font)
	{
		if (font->texture)
			mlxe_free_texture(window, font->texture);
		free(font);
	}
	return (NULL);
}

t_font	*mlxe_create_font(t_window *window,
	char *path, t_bool add_garbage)
{
	t_font	*font;

	font = malloc(sizeof(t_font));
	if (!font)
		return (exit_free(window, font, MLXE_ERROR_MALLOC));
	font->texture = mlxe_load_texture(window, path, FALSE);
	if (!font->texture)
		return (exit_free(window, font, window->error));
	font->size = 32;
	font->color = mlxe_color(255, 255, 255);
	save_all_width(font);
	if (add_garbage)
		if (!mlxe_add_garbage(window, font,
				(void (*)(t_window *, void *))mlxe_free_font))
			return (exit_free(window, font, MLXE_ERROR_MALLOC));
	return (font);
}
