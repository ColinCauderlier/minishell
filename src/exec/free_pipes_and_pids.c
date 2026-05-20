/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes_and_pids.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:48:43 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/19 18:51:07 by ccauderl         ###   ########.fr       */
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
	shell->exec.pipes = NULL;
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
