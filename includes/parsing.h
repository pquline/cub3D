/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/11 21:21:42 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <limits.h>
# include <fcntl.h>

# include <libft.h>
# include <mlxe.h>
# include <mlxe_structs.h>

# define ERROR			-1
# define MIN_RGB_COLOR	0
# define MAX_RGB_COLOR	255

# define COMMA_CHAR	','

# define COLOR_FLOOR	"F"
# define COLOR_CEILING	"C"

# define TEXTURE_NORTH	"NO"
# define TEXTURE_SOUTH	"SO"
# define TEXTURE_WEST	"WE"
# define TEXTURE_EAST	"EA"

/*
in map: replace player direction by empty tile
*/
typedef enum e_tile
{
	EMPTY	= 0,
	WALL	= 1,
	VOID	= INT_MAX,
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
	t_vector2	start_coords;
	char		start_direction;
}	t_map;

t_map	*init_map(void);
t_map	*parsing(char *path);

void	free_map(t_map *map);
void	*parsing_error(char *error);

#endif
