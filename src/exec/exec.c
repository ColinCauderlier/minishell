/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/22 14:32:03 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	execute_command(t_shell *shell, int i)
{
	char	*path;
	int		status;

	if (!shell->exec.commands[i][0] || shell->exec.commands[i][0][0] == '\0')
		free_all_error(shell, NULL, 127);
	status = check_builtin(shell->exec.commands[i]);
	if (status)
	{
		status = exec_builtin(shell, shell->exec.commands[i], status);
		free_all_error(shell, NULL, status);
	}
	path = find_path(shell->exec.commands[i][0], shell->envp);
	if (!path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n",
			shell->exec.commands[i][0]);
		free_all_error(shell, NULL, 127);
	}
	if (execve(path, shell->exec.commands[i], shell->envp) == -1)
		free_all_error(shell, &path, 126);
}

static int	exec_one_command(t_shell *shell)
{
	int	status;

	status = check_builtin(shell->exec.commands[0]);
	if (status)
	{
		status = exec_builtin(shell, shell->exec.commands[0], status);
		free_exec(shell);
		free_all_tokens(shell);
		shell->last_exit = status;
		return (status);
	}
	shell->exec.pids[0] = fork();
	if (shell->exec.pids[0] == -1)
		return (free_exec(shell), 1);
	if (shell->exec.pids[0] == 0)
		execute_command(shell, 0);
	waitpid(shell->exec.pids[0], &status, 0);
	free_exec(shell);
	if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit = 128 + WTERMSIG(status);
	else
		shell->last_exit = status;
	return (status);
}

static int	end_pipe_exec(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	close_all_pipes(shell);
	while (shell->exec.commands[i])
		waitpid(shell->exec.pids[i++], &status, 0);
	free_exec(shell);
	if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit = 128 + WTERMSIG(status);
	return (status);
}

static int	pipe_exec(t_shell *shell, int nb_commands)
{
	int	i;

	i = 0;
	while (shell->exec.commands[i])
	{
		shell->exec.pids[i] = fork();
		if (shell->exec.pids[i] == -1)
			return (free_exec(shell), 1);
		if (shell->exec.pids[i] == 0)
		{
			if (i == 0)
				first_cmd(shell);
			else if (i == nb_commands - 1)
				last_cmd(shell, i);
			else
				middle_cmd(shell, i);
		}
		i++;
	}
	return (end_pipe_exec(shell));
}

int	exec(t_shell *shell)
{
	int		status;
	int		nb_commands;

	status = check_syntax_shell(shell);
	if (status)
	{
		shell->last_exit = status;
		return (status);
	}
	nb_commands = init_exec(shell);
	if (nb_commands == -1)
		return (ft_fprintf(2, "minishell: A malloc has failed\n"), -1);
	if (nb_commands == -2)
		return (free_exec(shell), 0);
	else if (nb_commands == 1)
		return (exec_one_command(shell));
	else
		return (pipe_exec(shell, nb_commands));
	return (shell->last_exit);
}
