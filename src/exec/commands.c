/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:20:36 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:20 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	first_cmd(t_shell *shell)
{
	if (shell->exec.redirs[0].fd_in > 0)
		dup2(shell->exec.redirs[0].fd_in, STDIN_FILENO);
	if (shell->exec.redirs[0].fd_out > 1)
		dup2(shell->exec.redirs[0].fd_out, STDOUT_FILENO);
	else
		dup2(shell->exec.pipes[0][1], STDOUT_FILENO);
	close_all_pipes(shell);
	execute_command(shell, 0);
}

void	last_cmd(t_shell *shell, int i)
{
	if (shell->exec.redirs[i].fd_out > 1)
		dup2(shell->exec.redirs[i].fd_out, STDOUT_FILENO);
	if (shell->exec.redirs[i].fd_in > 0)
		dup2(shell->exec.redirs[i].fd_in, STDIN_FILENO);
	else
		dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(shell);
	execute_command(shell, i);
}

void	middle_cmd(t_shell *shell, int i)
{
	if (shell->exec.redirs[i].fd_in > 0)
		dup2(shell->exec.redirs[i].fd_in, STDIN_FILENO);
	else
		dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	if (shell->exec.redirs[i].fd_out > 0)
		dup2(shell->exec.redirs[i].fd_out, STDOUT_FILENO);
	else
		dup2(shell->exec.pipes[i][1], STDOUT_FILENO);
	close_all_pipes(shell);
	execute_command(shell, i);
}
