/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_hooks.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:49:37 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 18:43:42 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_HOOKS_H
# define MLXE_HOOKS_H

# include <mlx.h>
# include "mlxe.h"
# include <X11/X.h>
# include <X11/keysym.h>

void	init_keys(t_window *window);
int		handle_keydown(int keysym, t_window *data);
int		handle_keyrelease(int keysym, t_window *data);

#endif