/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrique <hrique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:59:35 by hesantan          #+#    #+#             */
/*   Updated: 2026/07/04 21:24:18 by hrique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(char *storage, int fd);
static char	*get_line(char *storage);
static char	*update_storage(char *storage);

static char	*free_and_null(char *reading, char *storage)
{
	free(reading);
	free(storage);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
		storage = ft_calloc(1, sizeof(char));
	storage = read_line(storage, fd);
	line = get_line(storage);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	storage = update_storage(storage);
	return (line);
}

static char	*read_line(char *storage, int fd)
{
	ssize_t	readed_bytes;
	char	*reading;

	reading = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readed_bytes = 1;
	while (!ft_strchr(storage, '\n') && (readed_bytes != 0))
	{
		readed_bytes = read(fd, reading, BUFFER_SIZE);
		if (readed_bytes == 0)
		{
			free(reading);
			return (storage);
		}
		storage = ft_strjoin(storage, reading);
		if (!storage)
			return (free_and_null(reading, NULL));
	}
	free(reading);
	return (storage);
}

static char	*get_line(char *storage)
{
	int		i;
	char	*ptr;

	if (!storage || storage[0] == '\0')
		return (NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i])
	{
		i++;
	}
	if (storage[i] == '\n')
		i++;
	ptr = ft_substr(storage, 0, i);
	return (ptr);
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
	if(!str || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}
