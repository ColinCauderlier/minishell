/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/19 18:08:49 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_read_loop(int fd, char **stash, char *buf)
{
	ssize_t	bytes;

	bytes = 1;
	while ((!*stash || !gnl_strchr(*stash, '\n')) && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			free(*stash);
			*stash = NULL;
			return (0);
		}
		buf[bytes] = '\0';
		if (bytes > 0)
		{
			*stash = gnl_strjoin(*stash, buf);
			if (!*stash)
				return (free(buf), 0);
		}
	}
	return (1);
}

static int	read_to_stash(int fd, char **stash)
{
	char	*buf;

	if (*stash && gnl_strchr(*stash, '\n'))
		return (1);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	if (!gnl_read_loop(fd, stash, buf))
		return (0);
	free(buf);
	return (1);
}

static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	size_t	i;
	char	*rest;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (free(stash), NULL);
	rest = gnl_substr(stash, i + 1, gnl_strlen(stash) - i - 1);
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_to_stash(fd, &stash[fd]))
		return (NULL);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
