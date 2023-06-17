/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:50:06 by dapereir          #+#    #+#             */
/*   Updated: 2023/06/12 16:17:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gnl_read_more(char **store, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*new_store;
	int		buffer_size;

	buffer_size = read(fd, buffer, BUFFER_SIZE);
	if (buffer_size > 0)
	{
		buffer[buffer_size] = '\0';
		new_store = ft_strjoin(*store, buffer);
		if (!new_store)
			return (-1);
		ft_free((void **)store);
		*store = new_store;
	}
	return (buffer_size);
}

static char	*gnl_extract_line(char **store, char *breakline)
{
	char	*line;
	char	*new_store;

	if (!*store)
		return (NULL);
	if (!breakline)
	{
		line = *store;
		*store = NULL;
		if (ft_strlen(line) == 0)
			return (ft_free((void **)&line));
		return (line);
	}
	line = ft_strndup(*store, breakline - *store + 1);
	if (!line)
		return (ft_free((void **)store));
	new_store = ft_strdup(breakline + 1);
	if (!new_store)
	{
		ft_free((void **)&line);
		return (ft_free((void **)store));
	}
	ft_free((void **)store);
	*store = new_store;
	return (line);
}

static char	*gnl_get_or_free(int fd, int free_store)
{
	static char		*store[OPEN_MAX];
	char			*breakline;
	int				buffer_size;
	char			*line;

	if (free_store)
		return (ft_free((void **)&store[fd]));
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!store[fd])
		store[fd] = ft_strdup("");
	if (!store[fd])
		return (NULL);
	breakline = ft_strchr(store[fd], '\n');
	buffer_size = 1;
	while (!breakline && buffer_size > 0)
	{
		buffer_size = gnl_read_more(store + fd, fd);
		if (buffer_size == -1)
			return (ft_free((void **)store + fd));
		breakline = ft_strchr(store[fd], '\n');
	}
	line = gnl_extract_line(store + fd, breakline);
	return (line);
}

char	*ft_gnl(int fd)
{
	return (gnl_get_or_free(fd, 0));
}

char	*ft_free_gnl(int fd)
{
	return (gnl_get_or_free(fd, 1));
}
