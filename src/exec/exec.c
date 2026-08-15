/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 17:04:07 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	exec_command_2(t_shell *shell, int i, char *path, struct stat statbuf)
{

	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", path);
		free_all_error(shell, NULL, 126);
	}
	if (access(path, F_OK) != 0)
	{
		if (ft_strchr(shell->exec.commands[i][0], '/'))
			ft_fprintf(2, "minishell: %s: No such file or directory\n",
				shell->exec.commands[i][0]);
		else
			ft_fprintf(2, "minishell: %s: command not found\n",
				shell->exec.commands[i][0]);
		free_all_error(shell, NULL, 127);
	}
	if (access(path, X_OK) != 0)
		free_all_error(shell, &path, 126);
	if (execve(path, shell->exec.commands[i], shell->envp) == -1)
		free_all_error(shell, &path, 126);
}

void	execute_command(t_shell *shell, int i)
{
	char		*path;
	int			status;
	struct stat	statbuf;

	if (!shell->exec.commands[i][0])
		free_all_error(shell, NULL, 127);
	status = check_builtin(shell->exec.commands[i]);
	if (status)
	{
		status = exec_builtin(shell, shell->exec.commands[i], status);
		free_all_error(shell, NULL, status);
	}
	path = find_path(shell->exec.commands[i][0], shell->envp);
	if (!path || shell->exec.commands[i][0][0] == '\0')
	{
		if (path)
			free(path);
		ft_fprintf(2, "minishell: %s: command not found\n",
			shell->exec.commands[i][0]);
		free_all_error(shell, NULL, 127);
	}
	exec_command_2(shell, i, path, statbuf);
}

static int	end_pipe_exec(t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	close_all_pipes(shell);
	while (shell->exec.commands[i])
	{
		waitpid(shell->exec.pids[i++], &status, 0);
		set_exit_status(shell, status);
	}
	free_exec(shell);
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
			setup_child_signals();
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
	int	status;
	int	nb_commands;

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
		return (exec_single_command(shell));
	return (pipe_exec(shell, nb_commands));
}
