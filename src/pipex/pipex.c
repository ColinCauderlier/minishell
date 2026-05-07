/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:20:36 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/04 11:57:42 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	end_loop(t_proc_args *args, int status)
{
	int	i;
	int	last_status;

	i = 0;
	last_status = 0;
	close_all_pipes(args);
	while (args->commands[i])
	{
		waitpid(args->pids[i], &status, 0);
		if (!args->commands[i + 1])
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (0);
}

static int	pipe_loop(t_proc_args *args, t_shell *shell)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	args->pids = malloc((shell->nb_token - 3) * sizeof(pid_t));
	while (args->commands[i])
	{
		args->pids[i] = fork();
		if (args->pids[i] == -1)
			return (error(args, -1, NULL), 1);
		else if (args->pids[i] == 0)
		{
			if (i == 0)
				first_cmd(args);
			else if (i == shell->nb_token - 4)
				last_cmd(args, i);
			else
				middle_cmd(args, i);
		}
		i++;
	}
	return (end_loop(args, status));
}

int	pipex(t_shell *shell)
{
	t_proc_args	args;
	int			error_var;

	error_var = 0;
	args.pids = NULL;
	init_args(&args, shell);
	args.commands = init_commands(shell);
	if (!args.commands)
		error_var = 1;
	if (error_var == 0)
		error_var = pipe_loop(&args, shell);
	free_all_pipes(&args);
	free(args.pids);
	free_commands(args.commands);
	return (error_var);
}
