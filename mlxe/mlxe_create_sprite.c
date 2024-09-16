/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_create_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:24:28 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:24:28 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlxe.h"

t_sprite	*mlxe_create_sprite(t_window *window, t_texture *texture,
			t_rect rect, t_bool add_garbage)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
	{
		window->error = MLXE_ERROR_MALLOC;
		return (NULL);
	}
	sprite->texture = texture;
	sprite->rect = rect;
	sprite->offset = (t_vector2){0, 0};
	if (add_garbage)
		if (!mlxe_add_garbage(window, sprite, mlxe_free))
			return (NULL);
	return (sprite);
}

void	mlxe_sprite_set_offset(t_sprite *sprite, t_vector2 offset)
{
	sprite->offset = offset;
}
