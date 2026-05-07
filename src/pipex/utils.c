/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:52:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/05 13:54:57 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_and_exit(t_proc_args *args, int code)
{
	free_all_pipes(args);
	free_commands(args->commands);
	exit(code);
}

char	***init_commands(t_shell *shell)
{
	char		**commands;
	int			i;
	t_token		*head;

	i = 0;
	head = shell->tokens;
	commands = ft_calloc(shell->nb_token - 2, sizeof(char **));
	while (i < shell->nb_token)
	{
		commands[i] = head->content;
		if (!commands[i])
			return (free_commands(commands), NULL);
		i++;
		head = head->next;
	}
	commands[i] = NULL;
	return (commands);
}

void	init_args(t_proc_args *args, t_shell *shell)
{
	args->pipes = ft_calloc(shell->nb_token - 2, sizeof(int *));
	args->envp = shell->str_envp;
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
