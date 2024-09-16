/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_load_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:08:35 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 15:49:06 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

static t_texture	*exit_free_(t_window *window, t_texture *texture, int error)
{
	window->error = error;
	if (texture)
	{
		if (texture->img)
			mlx_destroy_image(window->mlx, texture->img);
		free(texture);
	}
	return (NULL);
}

t_texture	*mlxe_load_texture(t_window *window, char *path, t_bool add_garbage)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (exit_free_(window, NULL, MLXE_ERROR_MALLOC));
	texture->img = mlx_xpm_file_to_image(window->mlx,
			path, &texture->size.x, &texture->size.y);
	if (!texture->img)
		return (exit_free_(window, texture, MLXE_ERROR_OPEN_FILE));
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->addr)
		return (exit_free_(window, texture, MLXE_ERROR_READ_FILE));
	if (add_garbage)
	{
		if (!mlxe_add_garbage(window, texture, mlxe_free_texture))
			return (exit_free_(window, texture, MLXE_ERROR_MALLOC));
	}
	return (texture);
}
