/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_free_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:35:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/12 22:35:04 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlxe.h"

void	mlxe_free_texture(t_window *window, void *texture)
{
	mlx_destroy_image(window->mlx, ((t_texture *)texture)->img);
	free(texture);
}
