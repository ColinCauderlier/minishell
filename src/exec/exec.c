/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/12 16:41:06 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

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
		if (list && list->next && is_redir_wo_word(list))
			list = list->next;
		if (list)
			list = list->next;
	}
	return (commands);
}

static void	execute_command(t_shell *shell, char **command)
{
	char	*path;

	if (!command[0] || command[0][0] == '\0')
	{
		free_split(command);
		exit(127);
	}
	path = find_path(command[0], shell->envp);
	if (!path)
	{
		if (ft_strncmp(command[0], ":", 2) != 0 && ft_strncmp(command[0], "!", 2) != 0)
			ft_fprintf(2, "minishell: %s: command not found\n", command[0]);
		free_split(command);
		free_all_tokens(shell);
		exit(127);
	}
	if (execve(path, command, shell->envp) == -1)
	{
		perror(path);
		free(path);
		free_split(command);
		exit(126);
	}
}

int	exec(t_shell *shell)
{
	int		pid;
	int		status;
	char	**commands;

	status = check_syntax_shell(shell);
	if (status)
	{
		shell->last_exit = status;
		return (status);
	}
	commands = get_commands(shell->tokens);
	if (!commands || !commands[0])
		return (free_split(commands), 0);
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		cd(commands[1], shell);
	else if (ft_strncmp(commands[0], "pwd", 4) == 0)
		pwd();
	else
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			execute_command(shell, commands);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit = 128 + WTERMSIG(status);
		else
			shell->last_exit = status;
	}
	free_split(commands);
	return (shell->last_exit);
}
