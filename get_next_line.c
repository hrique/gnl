/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrique <hrique@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:59:35 by hesantan          #+#    #+#             */
/*   Updated: 2026/07/04 17:45:24 by hrique           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	line = get_line(storage, line);
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
	unsigned int	readed_bytes;
	char			*reading;

	reading = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readed_bytes = 1;
	while (!ft_strchr(storage, '\n') && (readed_bytes > 0))
	{
		readed_bytes = read(fd, reading, BUFFER_SIZE);
		if (readed_bytes == 0)
			return (free_and_null(reading, storage));
		storage = ft_strjoin(storage, reading);
		if (!storage)
			return (free_and_null(reading, NULL));
	}
	free(reading);
	return (storage);
}

static char	*get_line(char *storage, char *line)
{
	int	i;

	i = 0;
	while (storage[i] != '\n' && storage[i])
	{
		i++;
	}
	line = ft_calloc(i, sizeof(char));
	line = ft_substr(storage, 0, i);
	return (line);
}

static char	*update_storage(char *storage)
{
	char	*str;
	int		i;
	int		j;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i])
		i++;
	j = 0;
	while (storage[j] != '\n' && storage[j])
		j++;
	str = ft_substr(storage, j, (i - j));
	return (str);
}
