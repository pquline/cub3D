/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:42:12 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/16 15:06:14 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

static void    raycast_init_dir(t_ray_calc* ray_calc)
{
	if (ray_calc->ray_dir_x < 0)
	{
		ray_calc->step_x = -1;
		ray_calc->side_dist_x = (ray_calc->ray.x - ray_calc->map_x) * ray_calc->delta_dist_x;
	}
	else
	{
		ray_calc->step_x = 1;
		ray_calc->side_dist_x = (ray_calc->map_x + 1.0 - ray_calc->ray.x) * ray_calc->delta_dist_x;
	}
	if (ray_calc->ray_dir_y < 0)
	{
		ray_calc->step_y = -1;
		ray_calc->side_dist_y = (ray_calc->ray.y - ray_calc->map_y) * ray_calc->delta_dist_y;
	}
	else
	{
		ray_calc->step_y = 1;
		ray_calc->side_dist_y = (ray_calc->map_y + 1.0 - ray_calc->ray.y) * ray_calc->delta_dist_y;
	}
}

static void	raycast_init(t_engine *engine, float angle, t_ray_calc* ray_calc)
{
	ray_calc->ray.dir = angle;
	ray_calc->ray.x = engine->camera.x;
	ray_calc->ray.y = engine->camera.y;
	ray_calc->ray_dir_x = cos(angle);
	ray_calc->ray_dir_y = sin(angle);
	ray_calc->map_x = (int)ray_calc->ray.x;
	ray_calc->map_y = (int)ray_calc->ray.y;
	if (ray_calc->ray_dir_y == 0)
		ray_calc->delta_dist_x = 1e30;
	else
		ray_calc->delta_dist_x = fabs(1 / ray_calc->ray_dir_x);
	if (ray_calc->ray_dir_y == 0)
		ray_calc->delta_dist_y = 1e30;
	else
		ray_calc->delta_dist_y = fabs(1 / ray_calc->ray_dir_y);
	raycast_init_dir(ray_calc);
}

static int	raycast_loop(t_engine *engine, t_ray_calc* ray_calc)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (ray_calc->side_dist_x < ray_calc->side_dist_y)
		{
			ray_calc->side_dist_x += ray_calc->delta_dist_x;
			ray_calc->map_x += ray_calc->step_x;
			ray_calc->side = 0; // Mur vertical
		}
		else
		{
			ray_calc->side_dist_y += ray_calc->delta_dist_y;
			ray_calc->map_y += ray_calc->step_y;
			ray_calc->side = 1; // Mur horizontal
		}
		if (engine->map->grid[ray_calc->map_y][ray_calc->map_x].id != EMPTY)
			hit = 1;
	}
	return (hit);
}

t_ray raycast(t_engine *engine, float angle)
{
	t_ray_calc	ray_calc;
	int			hit;

	raycast_init(engine, angle, &ray_calc);
	hit = raycast_loop(engine, &ray_calc);
	if (ray_calc.side == 0)
	{
		ray_calc.ray.dist = (ray_calc.map_x - ray_calc.ray.x + (1 - ray_calc.step_x) / 2.0) / ray_calc.ray_dir_x;
		if (ray_calc.step_x < 0)
			ray_calc.ray.side_hit = 3; // 3 = ouest
		else
			ray_calc.ray.side_hit = 1; // 1 = est
		ray_calc.ray.x_t = ray_calc.ray.y + ray_calc.ray.dist * ray_calc.ray_dir_y - floor(ray_calc.ray.y + ray_calc.ray.dist * ray_calc.ray_dir_y);
	}
	if (ray_calc.side == 1)
	{
		ray_calc.ray.dist = (ray_calc.map_y - ray_calc.ray.y + (1 - ray_calc.step_y) / 2.0) / ray_calc.ray_dir_y;
		if (ray_calc.step_y < 0)
			ray_calc.ray.side_hit = 0; // 0 = nord
		else
			ray_calc.ray.side_hit = 2; // 2 = sud
		ray_calc.ray.x_t = ray_calc.ray.x + ray_calc.ray.dist * ray_calc.ray_dir_x - floor(ray_calc.ray.x + ray_calc.ray.dist * ray_calc.ray_dir_x);
	}
	return (ray_calc.ray);
}
