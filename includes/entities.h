/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:55 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:59:49 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3D.h>

# define ENTITY_SPEED	0.01

/*
typedef struct s_entity
{
	t_game		*game;
	t_sprite	*sprites;
	float		pos[2];
	float		dir;
	void		(*update)(struct s_entity *entity);
	void		(*minimap)(struct s_entity *entity);
}				t_entity;
*/

t_bool	spawn_coin_entities(t_game *game, t_map *map);
t_bool	spawn_entities(t_game *game);

void	get_next_target(t_entity *enemy, t_enemy_type type, \
	t_vector2 player_pos, float player_dir);

void	player_update(t_entity *entity);
void	player_minimap(t_entity *entity);

void	orbe_update(t_entity *entity);
void	orbe_minimap(t_entity *entity);

void	ghost_update(t_entity *entity);
void	ghost_minimap(t_entity *entity);

#endif
