/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesantan <hesantan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:59:35 by hesantan          #+#    #+#             */
/*   Updated: 2026/07/31 16:47:16 by hesantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_and_null(char *reading, char *storage)
{
	free(reading);
	free(storage);
	return (NULL);
}

static char	*read_line(char *storage, int fd)
{
	ssize_t	readed_bytes;
	char	*reading;
	char	*tmp;

	reading = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!reading)
		return (free_and_null(NULL, storage));
	readed_bytes = 1;
	while (!ft_strchr(storage, '\n') && (readed_bytes != 0))
	{
		readed_bytes = read(fd, reading, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (free_and_null(reading, storage));
		if (readed_bytes == 0)
			return (free(reading), storage);
		reading[readed_bytes] = '\0';
		tmp = ft_strjoin(storage, reading);
		if (!tmp)
			return (free_and_null(reading, storage));
		free(storage);
		storage = tmp;
	}
	free(reading);
	return (storage);
}

static char	*get_line(char *storage)
{
	int		i;

	if (!storage || storage[0] == '\0')
		return (NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i])
		i++;
	if (storage[i] == '\n')
		i++;
	return (ft_substr(storage, 0, i));
}

static char	*update_storage(char *storage)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i])
		i++;
	j = 0;
	while (storage[j] && storage[j] != '\n')
		j++;
	if (storage[j] == '\0')
	{
		free(storage);
		return (NULL);
	}
	str = ft_substr(storage, j + 1, i - (j + 1));
	free(storage);
	if (!str || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage[FD_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	if (!storage[fd])
		storage[fd] = ft_calloc(1, sizeof(char));
	if (!storage[fd])
		return (NULL);
	if (!ft_strchr(storage[fd], '\n'))
		storage[fd] = read_line(storage[fd], fd);
	line = get_line(storage[fd]);
	if (!line)
	{
		storage[fd] = free_and_null(NULL, storage[fd]);
		return (NULL);
	}
	storage[fd] = update_storage(storage[fd]);
	return (line);
}
