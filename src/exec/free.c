/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:06:16 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/14 13:00:18 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void    close_fd(int fd[2])
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

void    free_all_pipes(t_shell *shell)
{
        int     i;

        i = 0;
        while (shell->exec.pipes[i])
        {
                free(shell->exec.pipes[i]);
                i++;
        }
        free(shell->exec.pipes);
}

void    close_all_pipes(t_shell *shell)
{
        int     i;

        i = 0;
        while (shell->exec.pipes[i])
        {
                close_fd(shell->exec.pipes[i]);
                i++;
        }
}

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


