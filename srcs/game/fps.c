/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:10:15 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 10:13:28 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <time.h>

t_time	get_time()
{
	struct timeval tv;
    struct timezone tz;
	gettimeofday(&tv, &tz);
	return tv;
}

float	get_delta(t_time start, t_time end)
{
	double elapsed = (end.tv_sec - start.tv_sec) * 1000.0;
	elapsed += (end.tv_usec - start.tv_usec) / 1000.0;
	return (float)elapsed;
}

int	get_fps(t_time start, t_time end)
{
	double elapsed = get_delta(start, end);
	return (int)(1000.0 / elapsed);
}

float	adaptive_speed(float speed, float delta)
{
	return speed * delta;
}
