/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:20:04 by lfarhi            #+#    #+#             */
/*   Updated: 2024/05/29 15:13:11 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

void	*gnl_memcpy(char *dst, char *src, size_t n);
int		gnl_strstr(char *str, char c);
size_t	gnl_strlen(char *str);
int		gnl_strcat_realloc(char **src, char *add);
void	gnl_strcpy(char *dst, char *src);

#endif