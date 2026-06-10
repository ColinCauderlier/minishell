/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:06:16 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/10 15:47:32 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

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
	shell->exec.commands = NULL;
}

void	free_close_redirs(t_shell *shell)
{
	int	i;
	int	nb_commands;

	i = 0;
	if (!shell->exec.redirs)
		return ;
	nb_commands = get_nb_pipes(shell) + 1;
	while (i < nb_commands)
	{
		if (shell->exec.redirs[i].fd_in > 0)
			close(shell->exec.redirs[i].fd_in);
		if (shell->exec.redirs[i].delimiter)
			unlink(shell->exec.redirs[i].fname_in);
		if (shell->exec.redirs[i].fd_out > 1)
			close(shell->exec.redirs[i].fd_out);
		i++;
	}
	free(shell->exec.redirs);
	shell->exec.redirs = NULL;
}

void	free_exec(t_shell *shell)
{
	close_all_pipes(shell);
	free_all_pipes(shell);
	free_commands(shell);
	free_close_redirs(shell);
	free(shell->exec.pids);
}

void	free_all_error(t_shell *shell, char **path, int exit_code)
{
	if (path)
	{
		perror(*path);
		free(*path);
	}
	free_exec(shell);
	free_envp(shell);
	free_all_tokens(shell);
	exit(exit_code);
}
