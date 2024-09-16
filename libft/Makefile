# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 16:05:08 by lfarhi            #+#    #+#              #
#    Updated: 2024/09/16 14:43:06 by lfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ./
SRCS = ${SRC}Utils/ft_atoi.c ${SRC}Memory/ft_bzero.c ${SRC}Memory/ft_calloc.c
SRCS += ${SRC}Ascii/ft_isalnum.c ${SRC}Ascii/ft_isalpha.c
SRCS += ${SRC}Ascii/ft_isascii.c ${SRC}Ascii/ft_isdigit.c ${SRC}Ascii/ft_isspace.c
SRCS += ${SRC}Ascii/ft_isprint.c ${SRC}Memory/ft_memchr.c ${SRC}Memory/ft_memcmp.c
SRCS += ${SRC}Memory/ft_memcpy.c ${SRC}Memory/ft_memmove.c
SRCS += ${SRC}Memory/ft_memset.c ${SRC}String/ft_strchr.c ${SRC}String/ft_strdup.c
SRCS += ${SRC}String/ft_strlcat.c ${SRC}String/ft_strlcpy.c
SRCS += ${SRC}String/ft_strlen.c ${SRC}String/ft_strncmp.c ${SRC}String/ft_strnstr.c
SRCS += ${SRC}String/ft_strrchr.c ${SRC}String/ft_tolower.c
SRCS += ${SRC}String/ft_toupper.c
SRCS += ${SRC}String/ft_substr.c ${SRC}String/ft_strjoin.c
SRCS += ${SRC}String/ft_strtrim.c ${SRC}Utils/ft_split.c ${SRC}Utils/ft_itoa.c
SRCS += ${SRC}String/ft_strmapi.c ${SRC}String/ft_striteri.c
SRCS += ${SRC}Print/ft_putchar_fd.c ${SRC}Print/ft_putstr_fd.c
SRCS += ${SRC}Print/ft_putendl_fd.c ${SRC}Print/ft_putnbr_fd.c
SRCS += ${SRC}List/ft_lstadd_back.c ${SRC}List/ft_lstadd_front.c
SRCS += ${SRC}List/ft_lstclear.c ${SRC}List/ft_lstdelone.c ${SRC}List/ft_lstiter.c
SRCS += ${SRC}List/ft_lstlast.c ${SRC}List/ft_lstmap.c
SRCS += ${SRC}List/ft_lstnew.c ${SRC}List/ft_lstsize.c
SRCS += ${SRC}List/ft_lstremove.c

SRCS += ${SRC}Gnl/get_next_line.c
SRCS += ${SRC}Gnl/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus