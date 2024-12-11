/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 15:21:10 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <mlxe.h>
# include <mlxe_structs.h>
# include <limits.h>

/*
in map: replace player direction by empty tile
*/
typedef enum e_tile
{
	EMPTY		= '0',
	WALL		= '1',
	VOID		= INT_MAX,
}	t_tile;

/*
for textures: from path relative to the map to path relative to the program
for t_colors: mlx_color(r, g, b)
*/
typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		f;
	t_color		c;
	t_tile		**grid;
	size_t		width;
	size_t		height;
	t_vector2	player_coords;
	char		direction;
}	t_map;

t_map	*parsing(char *path);
void	free_map(t_map *map);

#endif
