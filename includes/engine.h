/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:37:47 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/11 16:32:35 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <mlxe.h>
# include "parsing.h"

typedef struct s_engine
{
	t_window	*window;
	t_texture	*walls[4];
	t_map		*map;
	t_list		*entities;
}				t_engine;

void	engine_init(t_engine *engine, t_window *window, t_map *map);
void	render_engine(t_engine *engine);

#endif // ENGINE_H