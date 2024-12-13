/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/13 09:58:14 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* --------------------------------- HEADERS -------------------------------- */

# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include <libft.h>
# include <mlxe.h>
# include <mlxe_structs.h>

/* --------------------------------- MACROS --------------------------------- */

# define ERROR			-1
# define SIZE_EXT		4
# define MIN_RGB_COLOR	0
# define MAX_RGB_COLOR	255
# define MIN_RGB_LENGTH	1
# define MAX_RGB_LENGTH	3

# define COMMA_CHAR	','
# define NL_CHAR	'\n'
# define SLASH_CHAR	'/'
# define SPACE_CHAR	' '
# define EMPTY_CHAR	'0'
# define WALL_CHAR	'1'
# define DOOR_CHAR	'2'

# define CUB_EXT	".cub"

# define COLOR_FLOOR	"F"
# define COLOR_CEILING	"C"

# define TEXTURE_NORTH	"NO"
# define TEXTURE_SOUTH	"SO"
# define TEXTURE_WEST	"WE"
# define TEXTURE_EAST	"EA"

# define VALID_MAP_CHARS	"012NSWE "
# define PLAYER_MAP_CHARS	"NSWE"

/* ---------------------------------- ENUMS --------------------------------- */

typedef enum e_state
{
	PARSING_MAP,
	PARSING_OTHER,
}	t_state;

/*
in map: replace player direction by empty tile
*/
typedef enum e_tile_id
{
	EMPTY	= 0,
	WALL	= 1,
	DOOR	= 2,
	VOID	= INT_MAX,
}	t_tile_id;

/* ------------------------------- STRUCTURES ------------------------------- */

typedef struct s_tile
{
	t_tile_id	id;
	t_list		*entities;
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

typedef struct s_parsing
{
	char	*line;
	t_list	*cub;
	t_map	*map;
	t_state	state;
}	t_parsing;

/* -------------------------------- FUNCTIONS ------------------------------- */

char	*ft_strndup(const char *string, size_t size);

t_bool	parse_color(t_color *color, char *line);
t_bool	parse_map_line(t_parsing *parsing, size_t index);
t_bool	parse_texture(char **texture, char *path);

t_map	*parsing(char *path);

void	get_cub(t_parsing *parsing, char *path);
void	get_grid(t_parsing *parsing);
void	init_parsing(t_parsing *parsing);

void	*free_map(t_map *map);
void	*free_parsing(t_parsing *parsing);
void	*parsing_error(char *error);

#endif
