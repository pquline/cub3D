/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:32 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 10:13:28 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <entities.h>

void	update_entities(t_game *game)
{
	t_list	*current;
	t_entity	*entity;

	current = game->engine.entities;
	while (current)
	{
		entity = (t_entity *)current->content;
		entity->update(entity);
		current = current->next;
	}
}

void	main_loop(t_window *window, void *data)
{
	t_game	*game;
	t_time	start;
	t_time	end;

	game = (t_game *)data;
	update_entities(game);
	start = get_time();
	render_engine(&game->engine);
	draw_minimap(game);
	mlxe_render(window);
	mlxe_mouse_move(window, window->width / 2, 1000000);
	end = get_time();
	game->delta_time = get_delta(start, end);
}

t_bool	game_init(t_game *game, t_window *window, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window = window;
	if (!load_assets(&game->assets, window))
		return (FAILURE);
	engine_init(&game->engine, window, map);
	if (spawn_entities(game) == FAILURE)
		return (FAILURE);
	set_entity_pos(game->player, game->engine.camera.x, game->engine.camera.y);
	game->player->dir = game->engine.camera.dir;
	return (SUCCESS);
}

void	destroy_game(t_game *game)
{
	destory_engine(&game->engine);
	free_map(game->engine.map);
}
