/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:20:36 by ccauderl          #+#    #+#             */
/*   Updated: 2026/03/01 13:53:01 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static int	pipe_loop(t_proc_args *args, int argc)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	args->pids = malloc((argc - 3) * sizeof(pid_t));
	while (args->commands[i])
	{
		args->pids[i] = fork();
		if (args->pids[i] == -1)
			return (error(args, -1, NULL), 1);
		else if (args->pids[i] == 0)
		{
			if (i == 0)
				first_cmd(args);
			else if (i == argc - 4)
				last_cmd(args, i);
			else
				middle_cmd(args, i);
		}
		i++;
	}
	return (end_loop(args, status));
}

int	main(int argc, char **argv, char **envp)
{
	t_proc_args	args;
	int			error_var;

	error_var = 0;
	args.pids = NULL;
	check_nb_arguments(argc);
	init_args(&args, envp, argv, argc);
	args.commands = init_commands(argv, argc);
	if (!args.commands)
		error_var = 1;
	if (error_var == 0)
		error_var = pipe_loop(&args, argc);
	free_all_pipes(&args);
	free(args.pids);
	free_commands(args.commands);
	return (error_var);
}
