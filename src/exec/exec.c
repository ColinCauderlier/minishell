/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/08 14:32:48 by ccauderl         ###   ########.fr       */
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
	int	fdin_save;
	int	fdout_save;

	if (!shell->exec.commands[0] || !shell->exec.commands[0][0])
	{
		free_exec(shell);
		shell->last_exit = 0;
		return (0);
	}
	if ((shell->exec.redirs[0].fname_in && shell->exec.redirs[0].fd_in == -1) || (shell->exec.redirs[0].fname_out && shell->exec.redirs[0].fd_out == -1))
	{
		if (shell->exec.redirs[0].fd_in == -1 && shell->exec.redirs[0].fname_in)
			perror(shell->exec.redirs[0].fname_in);
		else
			perror(shell->exec.redirs[0].fname_out);
		free_all_error(shell, NULL, 1);
	}
	status = check_builtin(shell->exec.commands[0]);
	if (status)
	{
		fdin_save = dup(STDIN_FILENO);
		fdout_save = dup(STDOUT_FILENO);
		if (shell->exec.redirs[0].fd_in > 0)
			dup2(shell->exec.redirs[0].fd_in, STDIN_FILENO);
		if (shell->exec.redirs[0].fd_out > 0)
			dup2(shell->exec.redirs[0].fd_out, STDOUT_FILENO);
		status = exec_builtin(shell, shell->exec.commands[0], status);
		dup2(fdin_save, STDIN_FILENO);
		dup2(fdout_save, STDOUT_FILENO);
		close(fdin_save);
		close(fdout_save);
		free_exec(shell);
		free_all_tokens(shell);
		shell->last_exit = status;
		return (status);
	}
	shell->exec.pids[0] = fork();
	if (shell->exec.pids[0] == 0)
	{
		if (shell->exec.pids[0] == -1)
			return (free_exec(shell), 1);
		if (shell->exec.redirs[0].fd_in != -1)
			dup2(shell->exec.redirs[0].fd_in, STDIN_FILENO);
		if (shell->exec.redirs[0].fd_out != -1)
			dup2(shell->exec.redirs[0].fd_out, STDOUT_FILENO);
		if (shell->exec.pids[0] == -1)
			return (free_exec(shell), 1);
		if (shell->exec.pids[0] == 0)
			execute_command(shell, 0);
	}
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
		return (exec_one_command(shell));
	else
		return (pipe_exec(shell, nb_commands));
	return (shell->last_exit);
}
