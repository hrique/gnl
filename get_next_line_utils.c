/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesantan <hesantan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:59:32 by hesantan          #+#    #+#             */
/*   Updated: 2026/07/02 18:15:37 by hesantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;
	size_t			i;

	i = 0;
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	len2 = 0;
	while (s1)
		len1++;
	while (s2)
		len2++;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = (char *)malloc(sizeof(char) * (len1 + len2 +1));
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(strjoin + len1, s2, len2 + 1);
	return (strjoin);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size;

	size = 0;
	while (s)
		size++;
	if (size <= start)
		return (ft_strdup(""));
	if ((size - start) < len)
		len = size - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, &s[start], len + 1);
	return (ptr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	...
}

char	*ft_strchr(const char *s, int c)
{
	...
}
