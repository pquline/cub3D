/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2025/01/10 12:27:16 by lfarhi           ###   ########.fr       */
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
# define UNSET			-1
# define CUB_LENGTH		4
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

# define CUB_SUFFIX	".cub"

# define COLOR_FLOOR	"F"
# define COLOR_CEILING	"C"

# define TEXTURE_NORTH	"NO"
# define TEXTURE_SOUTH	"SO"
# define TEXTURE_WEST	"WE"
# define TEXTURE_EAST	"EA"
# define TEXTURE_DOOR	"DO"

# define VALID_MAP_CHARS	"012NSWE "
# define PLAYER_MAP_CHARS	"NSWE"
# define VALID_SURR_EMPTY	"\0\1"

# define ERR_MALLOC_TMAP	"Failed to allocate memory [t_map *]"
# define ERR_MALLOC_TLIST	"Failed to allocate memory [t_list *]"
# define ERR_MALLOC_TTILES	"Failed to allocate memory [t_tile **]"
# define ERR_MALLOC_TTILE	"Failed to allocate memory [t_tile *]"
# define ERR_MALLOC_STRING	"Failed to allocate memory [char *]"
# define ERR_CUB_SUFFIX		"Invalid [.cub] file extension"
# define ERR_CUB_FORMAT		"Invalid [.cub] file format"
# define ERR_CUB_OPEN		"Cannot open [.cub] file"
# define ERR_TEXTURE_PATH	"Missing texture path"
# define ERR_TEXTURE_MULT	"Multiple definitions of texture path"
# define ERR_COLOR			"Invalid color format"
# define ERR_TOO_BIG		"Map size must be less than INT_MAX"
# define ERR_INVALID_CHAR	"Map can only contain valid tiles [0/1/2/N/S/W/E/ ]"
# define ERR_PLAYERS		"Map can only contain one player tile [N/S/W/E]"
# define ERR_NO_PLAYER		"Map must contain a player tile [N/S/W/E]"
# define ERR_NOT_SURROUNDED	"Map must be surrounded by wall tiles [1]"
# define ERR_DOORS			"Map can only contain two door tiles [2]"
# define ERR_NO_EMPTY		"Map must contain at least one empty tile [0]"
# define ERR_DOOR_MISPLACED	"Doors [2] can only be placed like so:\n\
001    110\n\
121 or 020\n\
100    011"

/* -------------------------------- TYPEDEFS -------------------------------- */

typedef enum e_visited	t_visited;

/* ---------------------------------- ENUMS --------------------------------- */

typedef enum e_primary
{
	RED,
	GREEN,
	BLUE,
	PRIMARY_END,
}	t_primary;

typedef enum e_parsing_state
{
	PARSING_MAP,
	PARSING_METADATA,
}	t_parsing_state;

typedef enum e_tile_id
{
	EMPTY,
	WALL,
	DOOR,
	ENTITY,
	VOID,
	LEN_TILE_ID
}	t_tile_id;

/* ------------------------------- STRUCTURES ------------------------------- */

typedef struct s_tile
{
	t_tile_id	id;
	int			data;
	int			path_f;
}	t_tile;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*door;
	char		start_direction;
	size_t		width;
	size_t		height;
	t_visited	**visited;
	t_color		f;
	t_color		c;
	t_tile		**grid;
	t_vector2	start_coords;
}	t_map;

typedef struct s_parsing
{
	char			*line;
	t_list			*cub;
	t_map			*map;
	t_parsing_state	state;
}	t_parsing;

/* -------------------------------- FUNCTIONS ------------------------------- */

char	*ft_strndup(const char *string, size_t size);

t_bool	free_double_array(void **array, size_t size);
t_bool	get_cub(t_parsing *parsing, char *path);
t_bool	get_grid(t_parsing *parsing);
t_bool	init_parsing(t_parsing *parsing);
t_bool	map_is_valid(t_map *map);
t_bool	parse_color(t_color *color, char *line);
t_bool	parse_map_line(t_parsing *parsing, size_t index);
t_bool	parse_texture(char **texture, char *path);
t_bool	parsing_error(char *error);

t_map	*parsing(char *path);

void	*free_map(t_map *map);
void	*free_parsing(t_parsing *parsing);

#endif
