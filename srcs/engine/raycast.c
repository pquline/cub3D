/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:42:12 by lfarhi            #+#    #+#             */
/*   Updated: 2025/01/14 11:15:25 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <float.h>

static inline void	raycast_init_dir(t_ray_calc *ray_calc)
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
		ray_calc->delta_dist_x = FLT_MAX;
	else
		ray_calc->delta_dist_x = fabs(1 / ray_calc->ray_dir_x);
	if (ray_calc->ray_dir_y == 0)
		ray_calc->delta_dist_y = FLT_MAX;
	else
		ray_calc->delta_dist_y = fabs(1 / ray_calc->ray_dir_y);
	raycast_init_dir(ray_calc);
}

static int	raycast_loop(t_engine *engine, t_ray_calc *rc)
{
	int	iter;

	iter = 0;
	while (!rc->ray.hit && iter < 500)
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
			rc->ray.hit = 1;
		iter++;
	}
	return (rc->ray.hit);
}

static inline void	raycast_side(t_ray_calc *rc)
{
	if (rc->side == 0)
	{
		rc->ray.dist = (rc->map_x - rc->ray.x
				+ (1 - rc->step_x) * 0.5f) / rc->ray_dir_x;
		if (rc->step_x < 0)
			rc->ray.side_hit = 3;
		else
			rc->ray.side_hit = 1;
		rc->ray.x_t = fmodf(rc->ray.y + rc->ray.dist * rc->ray_dir_y, 1.0f);
	}
	if (rc->side == 1)
	{
		rc->ray.dist = (rc->map_y - rc->ray.y
				+ (1 - rc->step_y) * 0.5f) / rc->ray_dir_y;
		if (rc->step_y < 0)
			rc->ray.side_hit = 0;
		else
			rc->ray.side_hit = 2;
		rc->ray.x_t = fmodf(rc->ray.x + rc->ray.dist * rc->ray_dir_x, 1.0f);
	}
	if (rc->ray.side_hit == 3 || rc->ray.side_hit == 2)
		rc->ray.x_t = 1 - rc->ray.x_t;
}

t_ray_calc	raycast(t_engine *engine, float angle)
{
	t_ray_calc	ray_calc;

	raycast_init(engine, angle, &ray_calc);
	if (raycast_loop(engine, &ray_calc))
	{
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
