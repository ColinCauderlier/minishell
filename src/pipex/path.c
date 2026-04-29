/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:51:57 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 17:17:22 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_from_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

static char	*find_path_loop(char *command, char **paths)
{
	int		i;
	char	*path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*full_path;
	int		len;

	if (access(command, X_OK) == 0)
	{
		len = ft_strlen(command);
		full_path = malloc((len + 1) * sizeof(char));
		ft_strlcpy(full_path, command, len + 1);
		return (full_path);
	}
	paths = ft_split(get_path_from_envp(envp), ':');
	if (!paths)
		return (NULL);
	full_path = find_path_loop(command, paths);
	if (!full_path)
		return (free_split(paths), NULL);
	free_split(paths);
	return (full_path);
}
