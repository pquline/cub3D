/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_keys.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:09:30 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 16:44:16 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_KEYS_H
# define MLXE_KEYS_H

# include <X11/X.h>
# include <X11/keysym.h>

# define STATE_NOTHING 0x00
# define STATE_ONDOWN 0x01
# define STATE_ONPRESSED 0x02
# define STATE_ONRELEASE 0x03

# define MAX_KEYS 65536
# define MAX_MOUSE 6
# define MAX_ALL_KEYS 65542

# define MOUSE_LEFT 65537
# define MOUSE_MIDDLE 65538
# define MOUSE_RIGHT 65539
# define MOUSE_SCROLL_UP 65540
# define MOUSE_SCROLL_DOWN 65541

#endif