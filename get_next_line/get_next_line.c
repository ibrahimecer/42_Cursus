/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecer <iecer@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:22:28 by iecer             #+#    #+#             */
/*   Updated: 2024/02/05 11:47:05 by iecer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	*ft_free_cache(char **cache, int create_line)
{
	char	*line;

	if (!*cache)
		return (NULL);
	if (create_line == 1)
	{
		line = ft_strdup(*cache);
		free(*cache);
		*cache = NULL;
		return (line);
	}
	else if (create_line == 0)
	{
		if (*cache)
		{
			free(*cache);
			*cache = NULL;
		}
		return (NULL);
	}
	return (NULL);
}

static char	*ft_cpy(char *cache, char *buf)
{
	char	*res;

	res = 0;
	if (!cache && buf)
	{
		res = ft_strdup(buf);
		if (!res)
			return (NULL);
		return (res);
	}
	res = ft_strjoin(cache, buf);
	ft_free_cache(&cache, 0);
	return (res);
}

static char	*ft_remove_line(char *cache)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!cache)
		return (ft_free_cache(&cache, 0));
	while (cache[i] != '\n')
		++i;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free_cache(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = cache[j];
		++j;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_revise_cache(char *cache)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!cache)
		return (NULL);
	while (cache[i] != '\n')
		++i;
	if (cache[i + 1] == '\0')
		return (ft_free_cache(&cache, 0));
	res = ft_substr(cache, i + 1, ft_strlen(cache));
	if (!res)
	{
		ft_free_cache(&cache, 0);
		return (NULL);
	}
	ft_free_cache(&cache, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		read_count;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	read_count = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_cache(&stash, 0));
	while (read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if ((read_count <= 0 && !stash) || read_count == -1)
			return (ft_free_cache(&stash, 0));
		buffer[read_count] = '\0';
		stash = ft_cpy(stash, buffer);
		if (ft_control_newline(stash))
		{
			line = ft_remove_line(stash);
			if (!line)
				return (ft_free_cache(&stash, 0));
			return (stash = ft_revise_cache(stash), line);
		}
	}
	return (ft_free_cache(&stash, 1));
}
