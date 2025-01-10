/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:55 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 19:21:39 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <cub3D.h>

# define ENEMY_SPEED	0.03
# define BIG_ORBS_DIST	5

t_bool		big_orb_can_spawn(t_map *map, t_vector2 min, t_vector2 max);
t_bool		init_accessible_map(t_map *map);
t_bool		spawn_entities(t_game *game);

t_vector2	get_farthest_tile(t_map *map, t_vector2 player);

void		detect_collision(t_entity *enemy);
void		get_accessible_tiles(t_map *map, t_vector2 v);
void		get_next_target(t_entity *enemy, t_enemy_type type, t_vector2 pos);
void		sp_add_move(t_entity *entity, float x, float y, t_vector2 target);

void		big_orb_update(t_entity *entity);
void		big_orb_minimap(t_entity *entity);
void		ghost_update(t_entity *entity);
void		ghost_minimap(t_entity *entity);
void		orb_update(t_entity *entity);
void		orb_minimap(t_entity *entity);
void		player_update(t_entity *entity);
void		player_minimap(t_entity *entity);

#endif
