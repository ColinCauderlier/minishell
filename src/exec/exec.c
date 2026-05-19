/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/19 14:18:02 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	get_nb_pipes(t_shell *shell)
{
	int			count;
	t_token		*list;

	count = 0;
	list = shell->tokens;
	while (list && list->next)
	{
		if (list->token_type == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

char	**get_commands(t_token *tokens)
{
	t_token	*list;
	t_token	*command;
	int		len_command;
	int		i;
	char	**commands;

	len_command = 0;
	list = tokens;
	commands = NULL;
	while (list && list->token_type != PIPE)
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
			if (!commands)
				return (NULL);
			command = list;
			i = 0;
			while (i < len_command)
			{
				commands[i] = ft_strdup(command->content);
				if (!commands[i])
					return (NULL);
				command = command->next;
				i++;
			}
			commands[i] = NULL;
			list = command;
			continue ;
		}
		if (list && list->next && is_redir_wo_word(list))
			list = list->next;
		if (list->next)
			list = list->next;
	}
	return (commands);
}

void	execute_command(t_shell *shell, int i)
{
	char	*path;
	int		status;

	if (!shell->exec.commands[i][0] || shell->exec.commands[i][0][0] == '\0')
	{
		free_exec(shell);
		free_envp(shell);
		free_all_tokens(shell);
		exit(127);
	}
	status = check_builtin(shell->exec.commands[i]);
	if (status)
	{
		status = exec_builtin(shell, shell->exec.commands[i], status);
		free_exec(shell);
		free_envp(shell);
		free_all_tokens(shell);
		exit(status);
	}
	path = find_path(shell->exec.commands[i][0], shell->envp);
	if (!path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", shell->exec.commands[i][0]);
		free_exec(shell);
		free_envp(shell);
		free_all_tokens(shell);
		exit(127);
	}
	if (execve(path, shell->exec.commands[i], shell->envp) == -1)
	{
		perror(path);
		free(path);
		free_exec(shell);
		free_envp(shell);
		free_all_tokens(shell);
		exit(126);
	}
}

int	exec(t_shell *shell)
{
	int		status;
	int		nb_commands;
	int		i;

	status = check_syntax_shell(shell);
	if (status)
	{
		shell->last_exit = status;
		return (status);
	}
	nb_commands = init_exec(shell);
	if (nb_commands == -1)
	{
		ft_fprintf(2, "minishell: A malloc has failed\n");
		return (-1);
	}
	if (nb_commands == -2)
		return (free_exec(shell), 0);
	else if (nb_commands == 1)
	{
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
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit = 128 + WTERMSIG(status);
		else
			shell->last_exit = status;
	}
	else
	{
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
		i = 0;
		close_all_pipes(shell);
		while (shell->exec.commands[i])
			waitpid(shell->exec.pids[i++], &status, 0);
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit = 128 + WTERMSIG(status);
	}
	free_exec(shell);
	return (shell->last_exit);
}
