/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/10 19:06:23 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	ghost_update(t_entity *enemy)
{
	const t_enemy	*data = (t_enemy *)enemy->data;
	const float		dx = fabs((data->target.x + 0.5) - enemy->pos[0]);
	const float		dy = fabs((data->target.y + 0.5) - enemy->pos[1]);
	int				sp_idx;
	t_game			*game;

	game = (t_game *)enemy->game;
	if (dx * dx + dy * dy < ENEMY_SPEED + 0.01)
		get_next_target(enemy, data->type, \
			(t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
	if (dx > 0.01 && data->target.x + 0.5 < enemy->pos[0])
		sp_add_move(enemy, -ENEMY_SPEED, 0, data->target);
	else if (dx > 0.01)
		sp_add_move(enemy, ENEMY_SPEED, 0, data->target);
	if (dy > 0.01 && data->target.y + 0.5 < enemy->pos[1])
		sp_add_move(enemy, 0, -ENEMY_SPEED, data->target);
	else if (dy > 0.01)
		sp_add_move(enemy, 0, ENEMY_SPEED, data->target);
	detect_collision(enemy);
	sp_idx = data->type;
	if (player_is_invulnerable(game))
		sp_idx = 4;
	enemy->sprites = game->assets.enemy[sp_idx][game->current_time.tv_usec \
		/ 200000 % 4];
}

void	ghost_minimap(t_entity *enemy)
{
	t_camera	*camera;
	t_coords	coords;
	t_enemy		*data;
	t_game		*game;
	int			sp_idx;

	game = (t_game *)enemy->game;
	data = (t_enemy *)enemy->data;
	camera = &game->engine.camera;
	sp_idx = data->type;
	if (player_is_invulnerable(game))
		sp_idx = 4;
	coords = (t_coords){game->assets.map_enemy[sp_idx]->rect, \
		(t_rect){((enemy->pos[0] - camera->x + 10) * 10) - 8, \
		((enemy->pos[1] - camera->y + 10) * 10) - 8, 12, 12}};
	coords = mask_minimap(coords);
	draw_sprite_mask(game->window, \
		game->assets.map_enemy[sp_idx], \
		coords);
}
