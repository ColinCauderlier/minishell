/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:52:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 17:17:47 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free_split(commands[i]);
		i++;
	}
	free(commands);
}

void	free_split(char **splitted)
{
	int	i;

	i = 0;
	if (!splitted)
		return ;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

void	close_fd(int fd[2])
{
	if (!fd)
		return ;
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
}
