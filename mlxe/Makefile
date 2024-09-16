# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 16:08:55 by lfarhi            #+#    #+#              #
#    Updated: 2024/06/14 00:56:55 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmlxe.a
SRC = ./
SRCS = ${SRC}mlxe_create_sprite.c ${SRC}mlxe_draw_line.c \
${SRC}mlxe_draw_sprite.c ${SRC}mlxe_free_sprite.c ${SRC}mlxe_loop_end.c \
${SRC}mlxe_add_garbage.c ${SRC}mlxe_create_texture.c \
${SRC}mlxe_draw_pixel.c ${SRC}mlxe_draw_subtexture.c ${SRC}mlxe_free_texture.c\
${SRC}mlxe_init.c ${SRC}mlxe_render.c ${SRC}mlxe_clear.c ${SRC}mlxe_destroy.c \
${SRC}mlxe_draw_texture.c ${SRC}mlxe_get_pixel.c ${SRC}mlxe_loop.c \
${SRC}mlxe_load_texture.c ${SRC}mlxe_update_input.c ${SRC}mlxe_color.c \
${SRC}mlxe_draw_fillrect.c ${SRC}mlxe_draw_rect.c ${SRC}mlxe_free_garbage.c \
${SRC}mlxe_read_pixel.c ${SRC}mlxe_write_pixel.c \
${SRC}mlxe_handle_keys.c ${SRC}mlxe_draw_subtexture_size.c \
${SRC}mlxe_create_font.c ${SRC}mlxe_free_font.c \
${SRC}mlxe_font_set_color.c ${SRC}mlxe_font_set_size.c \
${SRC}mlxe_draw_text.c

OBJS = ${SRCS:.c=.o}

LIBFT = ../libft/libft.a
MINILIBX = ../minilibx/libmlx.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ../libft -I ../minilibx

all: ${NAME}

${NAME}: ${MINILIBX} ${LIBFT} ${OBJS}
	ar rcs ${NAME} ${OBJS}

${MINILIBX}:
	@make -C ../minilibx

${LIBFT}:
	@make -C ../libft

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re mlx libft