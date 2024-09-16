/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:20:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/10 12:57:56 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_exit_destroy(char *line, char *buffer, char *save_buffer)
{
	if (line)
		free(line);
	if (buffer)
		free(buffer);
	save_buffer[0] = '\0';
	return (NULL);
}

static char	*gnl_exit_success(char *line, char *buffer)
{
	if (buffer)
		free(buffer);
	return (line);
}

static int	gnl_strspit(char *buffer, char **line, char *save, int *found)
{
	long long		idx;

	idx = gnl_strstr(buffer, '\n');
	*found = idx != -1;
	if (idx != -1)
	{
		if (!gnl_strcat_realloc(line, buffer))
			return (0);
		gnl_strcpy(save, buffer + idx + 1);
		return (1);
	}
	if (!gnl_strcat_realloc(line, buffer))
		return (0);
	save[0] = '\0';
	return (1);
}

static char	*gnl_main(int fd, char *save_buffer, char *buffer, char *line)
{
	int	found;
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret < 0)
		return (gnl_exit_destroy(line, buffer, save_buffer));
	if (ret <= 0 && save_buffer[0] == '\0' && !line[0])
		return (gnl_exit_destroy(line, buffer, save_buffer));
	while (ret > 0)
	{
		buffer[ret] = '\0';
		if (!gnl_strspit(buffer, &line, save_buffer, &found))
			return (gnl_exit_destroy(line, buffer, save_buffer));
		if (found)
			return (gnl_exit_success(line, buffer));
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	return (gnl_exit_success(line, buffer));
}

char	*get_next_line(int fd)
{
	static char	save_buffer[BUFFER_SIZE + 1] = {0};
	char		*buffer;
	char		*line;
	int			found;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0
		|| !gnl_strspit(save_buffer, &line, save_buffer, &found))
		return (gnl_exit_destroy(line, NULL, save_buffer));
	if (found)
		return (line);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (gnl_exit_destroy(line, NULL, save_buffer));
	return (gnl_main(fd, save_buffer, buffer, line));
}
