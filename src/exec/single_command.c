/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:38:33 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 16:59:53 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	check_redirs_and_commands(t_shell *shell)
{
	if (!shell->exec.commands[0] || !shell->exec.commands[0][0])
	{
		free_exec(shell);
		shell->last_exit = 0;
		return (0);
	}
	if ((shell->exec.redirs[0].fname_in && shell->exec.redirs[0].fd_in == -1)
		|| (shell->exec.redirs[0].fname_out && shell->exec.redirs[0].fd_out
			== -1))
	{
		if (shell->exec.redirs[0].fd_in == -1 && shell->exec.redirs[0].fname_in)
			perror(shell->exec.redirs[0].fname_in);
		else
			perror(shell->exec.redirs[0].fname_out);
		free_exec(shell);
		shell->last_exit = 1;
		return (1);
	}
	return (-1);
}

static int	execute_single_builtin(t_shell *shell, int status)
{
	shell->exec.fdin_save = dup(STDIN_FILENO);
	shell->exec.fdout_save = dup(STDOUT_FILENO);
	if (shell->exec.redirs[0].fd_in > 0)
		dup2(shell->exec.redirs[0].fd_in, STDIN_FILENO);
	if (shell->exec.redirs[0].fd_out > 0)
		dup2(shell->exec.redirs[0].fd_out, STDOUT_FILENO);
	status = exec_builtin(shell, shell->exec.commands[0], status);
	dup2(shell->exec.fdin_save, STDIN_FILENO);
	dup2(shell->exec.fdout_save, STDOUT_FILENO);
	close(shell->exec.fdin_save);
	shell->exec.fdin_save = -1;
	close(shell->exec.fdout_save);
	shell->exec.fdout_save = -1;
	free_exec(shell);
	free_all_tokens(shell);
	shell->last_exit = status;
	return (status);
}

static void	execute_single_general_case(t_shell *shell)
{
	shell->exec.pids[0] = fork();
	if (shell->exec.pids[0] == 0)
	{
		if (shell->exec.redirs[0].fd_in != -1)
		{
			dup2(shell->exec.redirs[0].fd_in, STDIN_FILENO);
			close(shell->exec.redirs[0].fd_in);
			shell->exec.redirs[0].fd_in = -1;
		}
		if (shell->exec.redirs[0].fd_out != -1)
		{
			dup2(shell->exec.redirs[0].fd_out, STDOUT_FILENO);
			close(shell->exec.redirs[0].fd_out);
			shell->exec.redirs[0].fd_out = -1;
		}
		setup_child_signals();
		execute_command(shell, 0);
	}
}

int	exec_single_command(t_shell *shell)
{
	int	status;

	status = check_redirs_and_commands(shell);
	if (status != -1)
		return (status);
	status = check_builtin(shell->exec.commands[0]);
	if (status)
		return (execute_single_builtin(shell, status));
	execute_single_general_case(shell);
	if (shell->exec.pids[0] == -1)
		return (free_exec(shell), 1);
	waitpid(shell->exec.pids[0], &status, 0);
	set_exit_status(shell, status);
	free_exec(shell);
	return (status);
}
