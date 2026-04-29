/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:52:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 17:17:43 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_and_exit(t_proc_args *args, int code)
{
	free_all_pipes(args);
	free_commands(args->commands);
	exit(code);
}

char	***init_commands(char **argv, int argc)
{
	char	***commands;
	int		i;

	i = 0;
	commands = ft_calloc(argc - 2, sizeof(char **));
	while (i < argc - 3)
	{
		commands[i] = ft_split(argv[i + 2], ' ');
		if (!commands[i])
			return (free_commands(commands), NULL);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

void	init_args(t_proc_args *args, char **envp, char **argv, int argc)
{
	int	i;

	i = 0;
	args->pipes = ft_calloc(argc - 2, sizeof(int *));
	args->envp = envp;
	args->files[0] = argv[1];
	args->files[1] = argv[argc - 1];
	while (i < argc - 4)
	{
		args->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(args->pipes[i]) == -1)
		{
			error(args, -1, NULL);
			free_all_pipes(args);
			exit(1);
		}
		i++;
	}
	args->pipes[i] = NULL;
}

void	execute_command(t_proc_args *args, int i)
{
	char	*path;

	if (!args->commands[i][0] || args->commands[i][0][0] == '\0')
	{
		errno = 0;
		error(args, -1, NULL);
		free_and_exit(args, 127);
	}
	path = find_path(args->commands[i][0], args->envp);
	if (!path)
	{
		errno = 0;
		error(args, -1, args->commands[i]);
		free_and_exit(args, 127);
	}
	if (execve(path, args->commands[i], args->envp) == -1)
	{
		free(path);
		error(args, -1, args->commands[i]);
		free_and_exit(args, 126);
	}
}
