/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:39 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/18 15:57:26 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

static t_bool	line_init(t_engine *engine, t_rendering *r)
{
	t_ltxt	res;

	r->line_height = (int)(engine->window->buffer->size.y
			/ fmax(r->ray_calc.ray.dist * tan(engine->camera.fov / 2.0f), 0.1f));
	r->draw_start = -r->line_height / 2 + engine->window->buffer->size.y / 2;
	r->draw_end = r->line_height / 2 + engine->window->buffer->size.y / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= engine->window->buffer->size.y)
		r->draw_end = engine->window->buffer->size.y - 1;
	if (engine->render_block[r->ray_calc.ray.tile_id] == NULL)
		return (FALSE);
	res = engine->render_block[r->ray_calc.ray.tile_id](engine, r);
	if (res.texture == NULL)
		return (FALSE);
	r->texture = res.texture;
	r->tex_x = res.x;
	r->tex_x = r->tex_x % r->texture->size.x;
	return (TRUE);
}

static void	draw_line(t_engine *engine, t_rendering *r)
{
	int		y;
	int		d;
	int		tex_y;
	t_color	color;

	y = r->draw_start;
	while (y < r->draw_end)
	{
		d = y * 256 - engine->window->buffer->size.y * 128
			+ r->line_height * 128;
		tex_y = ((d * r->texture->size.y) / r->line_height) / 256;
		color = mlxe_get_pixel(r->texture, r->tex_x, tex_y);
		mlxe_draw_pixel(engine->window->buffer, r->screen_x, y, color);
		y++;
	}
}

void	render_line(t_engine *engine, t_rendering *r)
{
	if (r->ray_calc.ray.hit)
	{
		r->ray_calc.ray.dist *= cos(r->ray_calc.ray.dir - engine->camera.dir);
		if (line_init(engine, r))
			draw_line(engine,r);
	}
}

void	render_copy(t_rendering *from, t_rendering *to)
{
	to->ray_calc = from->ray_calc;
	to->camera_plane = from->camera_plane;
	to->camera_x = from->camera_x;
	to->ray_angle = from->ray_angle;
	to->line_height = from->line_height;
	to->draw_start = from->draw_start;
	to->draw_end = from->draw_end;
	to->tex_x = from->tex_x;
	to->screen_x = from->screen_x;
	to->texture = from->texture;
}

void	draw_map(t_engine *engine)
{
	t_rendering	r;

	r.camera_plane = engine->camera.fov / 2.0f;
	r.screen_x = 0;
	while (r.screen_x < engine->window->buffer->size.x)
	{
		r.camera_x = 2 * r.screen_x / (float)engine->window->buffer->size.x - 1;
		r.ray_angle = engine->camera.dir + r.camera_x * r.camera_plane;
		r.ray_calc = raycast_calc(engine, r.ray_angle);
		render_line(engine, &r);
		r.screen_x++;
	}
}
