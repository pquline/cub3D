/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghost.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:56:49 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/13 17:47:41 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

static void	ghost_move(t_game *game, t_entity *enemy, t_enemy *data)
{
	float	d[2];
	float	adapt_speed;

	adapt_speed = adaptive_speed(ENEMY_SPEED, game->delta_time);
	d[0] = fabs((data->target.x + 0.5) - enemy->pos[0]);
	d[1] = fabs((data->target.y + 0.5) - enemy->pos[1]);
	if (d[0] * d[0] + d[1] * d[1] < adapt_speed + 0.01)
		get_next_target(enemy, data->type, \
			(t_vector2){(int)game->player->pos[0], (int)game->player->pos[1]});
	d[0] = fabs((data->target.x + 0.5) - enemy->pos[0]);
	d[1] = fabs((data->target.y + 0.5) - enemy->pos[1]);
	if (d[0] > 0.01 && data->target.x + 0.5 < enemy->pos[0])
		sp_add_move(enemy, -adapt_speed, 0, data->target);
	else if (d[0] > 0.01)
		sp_add_move(enemy, adapt_speed, 0, data->target);
	if (d[1] > 0.01 && data->target.y + 0.5 < enemy->pos[1])
		sp_add_move(enemy, 0, -adapt_speed, data->target);
	else if (d[1] > 0.01)
		sp_add_move(enemy, 0, adapt_speed, data->target);
}

void	ghost_update(t_entity *enemy)
{
	t_enemy	*data;
	t_game	*game;
	int		sp_idx;

	data = (t_enemy *)enemy->data;
	game = (t_game *)enemy->game;
	ghost_move(game, enemy, data);
	if (enemy->pos[0] == data->last_pos[0]
		&& enemy->pos[1] == data->last_pos[1])
	{
		set_entity_pos(enemy, (int)data->last_pos[0] + 0.5f,
			(int)data->last_pos[1] + 0.5f);
		data->target = (t_vector2){enemy->pos[0], enemy->pos[1]};
	}
	data->last_pos[0] = enemy->pos[0];
	data->last_pos[1] = enemy->pos[1];
	(detect_collision(enemy), sp_idx = data->type);
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

static t_bool	init_enemy_data(t_entity *enemy, t_enemy_type type)
{
	t_enemy	*ghost;

	ghost = (t_enemy *)ft_calloc(1, sizeof(t_enemy));
	if (ghost == NULL)
		return (FAILURE);
	ghost->type = type;
	ghost->mode = ENEMY_CHASING;
	ghost->red = NULL;
	enemy->data = ghost;
	return (SUCCESS);
}

t_entity	*ghost_spawn(t_game *game, t_vector2 pos, int index)
{
	t_enemy			*data;
	t_entity		*enemy;

	enemy = spawn_entity(&game->engine, game, (t_efunc){&ghost_update, \
		&ghost_minimap, free}, game->assets.enemy[index][0]);
	if (enemy == NULL)
		return (NULL);
	set_entity_pos(enemy, (float)pos.x + 0.5, (float)pos.y + 0.5);
	if (init_enemy_data(enemy, index) == FAILURE)
		return (NULL);
	data = (t_enemy *)enemy->data;
	data->target = (t_vector2){(int)enemy->pos[0], (int)enemy->pos[1]};
	data->last_pos[0] = enemy->pos[0];
	data->last_pos[1] = enemy->pos[1];
	return (enemy);
}
