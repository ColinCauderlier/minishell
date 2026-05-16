/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:06:16 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/16 14:01:28 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	close_fd(int fd[2])
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

void	free_all_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->exec.pipes[i])
	{
		free(shell->exec.pipes[i]);
		i++;
	}
	free(shell->exec.pipes);
}

void	close_all_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->exec.pipes[i])
	{
		close_fd(shell->exec.pipes[i]);
		i++;
	}
}

void	free_commands(t_shell *shell)
{
	int	i;
	int	nb_commands;

	i = 0;
	if (!shell->exec.commands)
		return ;
	nb_commands = get_nb_pipes(shell) + 1;
	while (i < nb_commands)
	{
		if (shell->exec.commands[i])
			free_split(shell->exec.commands[i]);
		i++;
	}
	free(shell->exec.commands);
}

void	free_exec(t_shell *shell)
{
	close_all_pipes(shell);
	free_all_pipes(shell);
	free_commands(shell);
	free(shell->exec.pids);
}
