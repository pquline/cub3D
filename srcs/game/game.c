/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:51:32 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/12 19:08:44 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>
#include <stdio.h>

void want_to_move(t_engine *engine, float x, float y)
{
	if (x < 0 || x >= engine->map->width || y < 0 || y >= engine->map->height)
		return ;
	if (engine->map->grid[(int)y][(int)x].id != EMPTY)
		return ;
	// Taille du carré de collision (0.2)
    float half_size = 0.05;  // La moitié de la taille du carré (0.2 / 2)

    // Vérifier si les coins autour de la position souhaitée sont libres
    for (float dx = -half_size; dx <= half_size; dx += half_size) {
        for (float dy = -half_size; dy <= half_size; dy += half_size) {
            int check_x = (int)(x + dx);
            int check_y = (int)(y + dy);

            // Vérifier les limites du terrain et si la case est occupée
            if (check_x < 0 || check_x >= (int)engine->map->width || check_y < 0 || check_y >= (int)engine->map->height)
                return;  // Si la position est en dehors de la carte, on annule le déplacement

            if (engine->map->grid[check_y][check_x].id != EMPTY)
                return;  // Si la case est occupée, on annule le déplacement
        }
    }

	float mov_dir = atan2(y - engine->camera.y, x - engine->camera.x);
	t_ray ray = raycast(engine, mov_dir);
	float dist = sqrt(pow(engine->camera.x - x, 2) + pow(engine->camera.y - y, 2));
	if (ray.dist < dist)
		return ;
	engine->camera.x = x;
	engine->camera.y = y;
}

void add_move(t_engine *engine, float x, float y)
{
	want_to_move(engine, engine->camera.x + x, engine->camera.y + y);
}

void	main_loop(t_window *window, void *data)
{
	t_game	*game;

	game = (t_game *)data;
	//move forward
	if (mlxe_is_key_pressed(window, XK_w))
		add_move(&game->engine, cos(game->engine.camera.dir) * 0.01, sin(game->engine.camera.dir) * 0.01);
	//move backward
	if (mlxe_is_key_pressed(window, XK_s))
		add_move(&game->engine, -cos(game->engine.camera.dir) * 0.01, -sin(game->engine.camera.dir) * 0.01);
	//strafe right
	if (mlxe_is_key_pressed(window, XK_d))
		add_move(&game->engine, cos(game->engine.camera.dir + M_PI_2) * 0.01, sin(game->engine.camera.dir + M_PI_2) * 0.01);
	//strafe left
	if (mlxe_is_key_pressed(window, XK_a))
		add_move(&game->engine, cos(game->engine.camera.dir - M_PI_2) * 0.01, sin(game->engine.camera.dir - M_PI_2) * 0.01);
	if (mlxe_is_key_pressed(window, XK_Left))
		game->engine.camera.dir -= 0.01;
	if (mlxe_is_key_pressed(window, XK_Right))
		game->engine.camera.dir += 0.01;
	render_engine(&game->engine);
	draw_minimap(game);
	mlxe_render(window);
}

t_bool	game_init(t_game *game, t_window *window, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	game->window = window;
	if (!load_assets(&game->assets, window))
		return (FAILURE);
	engine_init(&game->engine, window, map);
	return (SUCCESS);
}

t_bool	load_assets(t_assets *assets, t_window *window)
{
	assets->minimap_entities = mlxe_load_texture(window, "assets/UI/minimap_entities.xpm", TRUE);//TODO check if it's loaded
	printf("minimap_entities: %p\n", assets->minimap_entities);
	assets->player[0] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){0,0,48,44}, TRUE);
	assets->player[1] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){58,0,48,44}, TRUE);
	assets->player[2] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){118,0,48,44}, TRUE);
	assets->player[3] = mlxe_create_sprite(window, assets->minimap_entities,(t_rect){178,0,48,44}, TRUE);
	assets->player[4] = assets->player[2];
	assets->player[5] = assets->player[1];
	assets->player_anim = 0;
	printf("player[0]: %p\n", assets->player[0]);
	return (SUCCESS);
}