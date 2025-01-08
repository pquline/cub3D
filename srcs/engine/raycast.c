/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:42:12 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/08 13:43:43 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <float.h>

static void	raycast_init_dir(t_ray_calc *ray_calc)
{
	if (ray_calc->ray_dir_x < 0)
	{
		ray_calc->step_x = -1;
		ray_calc->side_dist_x = (ray_calc->ray.x - ray_calc->map_x)
			* ray_calc->delta_dist_x;
	}
	else
	{
		ray_calc->step_x = 1;
		ray_calc->side_dist_x = (ray_calc->map_x + 1.0 - ray_calc->ray.x)
			* ray_calc->delta_dist_x;
	}
	if (ray_calc->ray_dir_y < 0)
	{
		ray_calc->step_y = -1;
		ray_calc->side_dist_y = (ray_calc->ray.y - ray_calc->map_y)
			* ray_calc->delta_dist_y;
	}
	else
	{
		ray_calc->step_y = 1;
		ray_calc->side_dist_y = (ray_calc->map_y + 1.0 - ray_calc->ray.y)
			* ray_calc->delta_dist_y;
	}
}

static void	raycast_init(t_engine *engine, float angle, t_ray_calc *ray_calc)
{
	ray_calc->ray.hit = FALSE;
	ray_calc->ray.dir = angle;
	ray_calc->ray.x = engine->camera.x;
	ray_calc->ray.y = engine->camera.y;
	ray_calc->ray_dir_x = cos(angle);
	ray_calc->ray_dir_y = sin(angle);
	ray_calc->map_x = (int)ray_calc->ray.x;
	ray_calc->map_y = (int)ray_calc->ray.y;
	if (ray_calc->ray_dir_x == 0)
		ray_calc->delta_dist_x = 1e30;
	else
		ray_calc->delta_dist_x = fabs(1 / ray_calc->ray_dir_x);
	if (ray_calc->ray_dir_y == 0)
		ray_calc->delta_dist_y = 1e30;
	else
		ray_calc->delta_dist_y = fabs(1 / ray_calc->ray_dir_y);
	raycast_init_dir(ray_calc);
}

static int	raycast_loop(t_engine *engine, t_ray_calc *rc)
{
	int	hit;
	int	iter;

	hit = 0;
	iter = 0;
	while (!hit && iter < 500)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		rc->ray.tile_id = engine->map->grid[rc->map_y][rc->map_x].id;
		if (engine->map->grid[rc->map_y][rc->map_x].id != EMPTY)
			hit = 1;
		iter++;
	}
	return (hit);
}

void	raycast_side(t_ray_calc *ray_calc)
{
	if (ray_calc->side == 0)
	{
		ray_calc->ray.dist = (ray_calc->map_x - ray_calc->ray.x
				+ (1 - ray_calc->step_x) / 2.0) / ray_calc->ray_dir_x;
		if (ray_calc->step_x < 0)
			ray_calc->ray.side_hit = 3;
		else
			ray_calc->ray.side_hit = 1;
		ray_calc->ray.x_t = ray_calc->ray.y
			+ ray_calc->ray.dist * ray_calc->ray_dir_y
			- floor(ray_calc->ray.y + ray_calc->ray.dist * ray_calc->ray_dir_y);
	}
	if (ray_calc->side == 1)
	{
		ray_calc->ray.dist = (ray_calc->map_y - ray_calc->ray.y
				+ (1 - ray_calc->step_y) / 2.0) / ray_calc->ray_dir_y;
		if (ray_calc->step_y < 0)
			ray_calc->ray.side_hit = 0;
		else
			ray_calc->ray.side_hit = 2;
		ray_calc->ray.x_t = ray_calc->ray.x
			+ ray_calc->ray.dist * ray_calc->ray_dir_x
			- floor(ray_calc->ray.x + ray_calc->ray.dist * ray_calc->ray_dir_x);
	}
}

t_ray_calc	raycast(t_engine *engine, float angle)
{
	t_ray_calc	ray_calc;
	int			hit;

	raycast_init(engine, angle, &ray_calc);
	hit = raycast_loop(engine, &ray_calc);
	if (hit)
	{
		ray_calc.ray.hit = TRUE;
		raycast_side(&ray_calc);
		ray_calc.ray.x = ray_calc.map_x;
		ray_calc.ray.y = ray_calc.map_y;
	}
	else
	{
		ray_calc.ray.dist = FLT_MAX;
		ray_calc.ray.hit = FALSE;
	}
	return (ray_calc);
}
