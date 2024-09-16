/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:49:54 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/14 15:47:10 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_STRUCTS_H
# define MLXE_STRUCTS_H

# include <libft.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define SUCCESS 1
# define FAILURE 0

# define MLXE_ERROR_NONE 0
# define MLXE_ERROR_MALLOC 1
# define MLXE_ERROR_OPEN_FILE 2
# define MLXE_ERROR_READ_FILE 3

typedef int				t_bool;
typedef struct s_window	t_window;
typedef unsigned int	t_uint;
typedef unsigned int	t_color;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}				t_rect;

typedef struct s_coords
{
	t_rect	src;
	t_rect	dest;
}				t_coords;

typedef struct s_vector2
{
	int	x;
	int	y;
}				t_vector2;

typedef struct s_texture
{
	void		*img;
	t_vector2	size;
	char		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_sprite
{
	t_texture	*texture;
	t_rect		rect;
	t_vector2	offset;
}				t_sprite;

typedef struct s_font
{
	t_texture	*texture;
	t_color		color;
	int			size;
	int			widths[128 - 32][2];
}				t_font;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_garbage
{
	void	*ptr;
	void	(*free)(t_window *, void *);
}				t_garbage;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_texture	*buffer;
	t_list		*garbage;
	t_bool		running;
	void		*data;
	void		(*funct_ptr)(t_window *, void *data);
	char		keys[MAX_ALL_KEYS];
	t_vector2	mouse;
	int			error;
}				t_window;

#endif