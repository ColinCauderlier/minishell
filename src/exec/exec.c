/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/14 12:57:41 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	check_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (2);
	return (0);
}

static int	exec_builtin(t_shell *shell, char **command, int id)
{
	if (id == 1)
		return (cd(command[1], shell));
	if (id == 2)
		return (pwd());
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
		if (list->next)
			list = list->next;
	}
	return (commands);
}

void	execute_command(t_shell *shell, int i)
{
	char	*path;
	int	status;

	if (!shell->exec.commands[i][0] || shell->exec.commands[i][0][0] == '\0')
	{
		free_commands(shell->exec.commands);
		exit(127);
	}
	status = check_builtin(shell->exec.commands[i][0]);
	if (status)
	{
		status = exec_builtin(shell, shell->exec.commands[i], status);
		close_all_pipes(shell);
		free_all_pipes(shell);
		free(shell->exec.pids);
		free_commands(shell->exec.commands);
		free_all_tokens(shell);
		exit (status);
	}
	path = find_path(shell->exec.commands[i][0], shell->envp);
	if (!path)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", shell->exec.commands[i][0]);
		close_all_pipes(shell);
		free_all_pipes(shell);
		free(shell->exec.pids);
		free_commands(shell->exec.commands);
		free_all_tokens(shell);
		exit(127);
	}
	if (execve(path, shell->exec.commands[i], shell->envp) == -1)
	{
		perror(path);
		free(path);
		close_all_pipes(shell);
		free_all_pipes(shell);
		free(shell->exec.pids);
		free_all_tokens(shell);
		free_commands(shell->exec.commands);
		exit(126);
	}
}

int	get_nb_pipes(t_shell *shell)
{
	int			count;
	t_token 	*list;

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

int	init_exec(t_shell *shell)
{
	int	i;
	int	nb_pipes;
	t_token	*list;

	i = 0;
	nb_pipes = get_nb_pipes(shell);
	shell->exec.commands = ft_calloc(nb_pipes + 2, sizeof(char **));
	if (!shell->exec.commands)
		return (-1);
	shell->exec.commands[nb_pipes + 1] = NULL;
	shell->exec.pids = ft_calloc(nb_pipes + 2, sizeof(int));
	if (!shell->exec.pids)
		return (free(shell->exec.commands), -1);
	shell->exec.pipes = ft_calloc(nb_pipes + 1, sizeof(int *));
	if (!shell->exec.pipes)
		return (free(shell->exec.pids), free(shell->exec.commands), -1);
	while (i < nb_pipes)
	{
		shell->exec.pipes[i] = ft_calloc(2, sizeof(int));
		if (!shell->exec.pipes[i])
		{
			free_all_pipes(shell);
			return (-1);
		}
		if (pipe(shell->exec.pipes[i]) == -1)
		{
			free_all_pipes(shell);
			return (-1);
		}
		i++;
	}
	shell->exec.pipes[nb_pipes] = NULL;
	i = 0;
	list = shell->tokens;
	while (i < nb_pipes + 1)
	{
		shell->exec.commands[i] = get_commands(list);
		if (!shell->exec.commands[i])
		{
			free_commands(shell->exec.commands);
			exit(127);
		}
		while (list->next && list->token_type != PIPE)
			list = list->next;
		if (list->next)
			list = list->next;
		i++;
	}
	shell->exec.commands[i] = NULL;
	return (nb_pipes + 1);
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
		ft_fprintf(2, "A malloc has failed\n");
		return (-1);
	}
	if (!shell->exec.commands || !shell->exec.commands[0])
		return (free_commands(shell->exec.commands), 0);
	else if (nb_commands == 1)
	{
		shell->exec.pids[0] = fork();
		if (shell->exec.pids[0] == -1)
		{
			close_all_pipes(shell);
			free_all_pipes(shell);
			free(shell->exec.pids);
			free_commands(shell->exec.commands);
			return (1);
		}
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
			{
				close_all_pipes(shell);
				free_all_pipes(shell);
				free(shell->exec.pids);
				free_commands(shell->exec.commands);
				return (1);
			}
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
		{
			waitpid(shell->exec.pids[i], &status, 0);
			if (!shell->exec.commands[i + 1])
				shell->last_exit = status;
			i++;
		}	
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit = 128 + WTERMSIG(status);
	}
	close_all_pipes(shell);
	free_all_pipes(shell);
	free(shell->exec.pids);
	free_commands(shell->exec.commands);
	return (shell->last_exit);
}
