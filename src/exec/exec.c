/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/07 17:56:36 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	is_redir_type(t_token *tkn)
{
	if (tkn->token_type == REDIR_IN || tkn->token_type == REDIR_OUT)
		return (1);
	if (tkn->token_type == HEREDOC || tkn->token_type == REDIR_OUT_APP_MODE)
		return (1);
	return (0);
}

static int	check_syntax_redir(t_shell *shell)
{
	t_token	*list;
	int		nb_redir;

	list = shell->tokens;
	nb_redir = 0;
	while (list && list->next)
	{
		if (is_redir_type(list))
		{
			nb_redir++;
			if (list->next->token_type != WORD)
				return (1);
		}
		else if (list->token_type == PIPE)
			nb_redir = 0;
		if (nb_redir >= 2)
			return (1);
		list = list->next;
	}
	return (0);
}

static int	check_syntax_pipes(t_shell *shell)
{
	t_token	*list;

	list = shell->tokens;
	while (list && list->next)
	{
		if (list->token_type == PIPE)
		{
			if (!list->next || list->next->token_type == PIPE)
				return (1);
		}
		list = list->next;
	}
	return (0);
}

static char	**get_commands(t_token *tokens)
{
	t_token	*list;
	t_token	*command;
	int		len_command;
	int		i;
	char	**commands;

	len_command = 0;
	list = tokens;
	commands = NULL;
	while (list && list->next && list->token_type != PIPE)
	{
		if (list->token_type == WORD)
		{
			command = list;
			while (command && command->token_type == WORD)
			{
				len_command++;
				command = command->next;
			}
			commands = malloc((len_command + 1) * sizeof(char *));
			command = list;
			i = 0;
			while (i < len_command)
			{
				commands[i] = ft_strdup(command->content);
				if (!commands[i])
					return (free_split(commands), NULL);
				command = command->next;
				i++;
			}
			commands[i] = NULL;
			list = command;
			continue ;
		}
		if (list && list->next && is_redir_type(list))
			list = list->next;
		if (list)
			list = list->next;
	}
	return (commands);
}

static int	execute_command(char **envp, char **command)
{
	char	*path;

	if (!command[0] || command[0][0] == '\0')
	{
		//      errno = 0;
		//      error(args, -1, NULL);
		//      free_and_exit(args, 127);
		free_split(command);
		exit(127);
	}
	path = find_path(command[0], envp);
	if (!path)
	{
		//      errno = 0;
		//      error(args, -1, args->commands[i]);
		//      free_and_exit(args, 127);
		free_split(command);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
	{
		perror(path);
		free(path);
		//      error(args, -1, args->commands[i]);
		//      free_and_exit(args, 126);
		free_split(command);
		exit(126);
	}
	return (0);
}

int	exec(t_shell *shell)
{
	int		pid;
	int		status;
	char	**commands;

	if (check_syntax_pipes(shell) || check_syntax_redir(shell))
			return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execute_command(shell->str_envp, get_commands(shell->tokens));
	waitpid(pid, &status, 0);
	return (status);
}
