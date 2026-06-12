/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 13:44:53 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	init_pipes(t_shell *shell, int nb_pipes)
{
	int	i;

	i = 0;
	shell->exec.pipes = ft_calloc(nb_pipes + 1, sizeof(int *));
	if (!shell->exec.pipes)
		return (free(shell->exec.pids), free(shell->exec.commands), 1);
	while (i < nb_pipes)
	{
		shell->exec.pipes[i] = ft_calloc(2, sizeof(int));
		if (!shell->exec.pipes[i])
			return (free_exec(shell), 1);
		if (pipe(shell->exec.pipes[i]) == -1)
			return (free_exec(shell), 1);
		i++;
	}
	shell->exec.pipes[nb_pipes] = NULL;
	return (0);
}

static int	init_commands(t_shell *shell, int nb_pipes)
{
	int		i;
	t_token	*list;

	i = 0;
	list = shell->tokens;
	while (i < nb_pipes + 1)
	{
		shell->exec.commands[i] = get_commands(list);
		if (!shell->exec.commands[i])
			return (free_commands(shell), 1);
		while (list->next && list->token_type != PIPE)
			list = list->next;
		if (list->next && list->token_type == PIPE)
			list = list->next;
		i++;
	}
	shell->exec.commands[i] = NULL;
	return (0);
}

int	init_exec(t_shell *shell)
{
	int	nb_pipes;

	shell->exec.fdin_save = -1;
	shell->exec.fdout_save = -1;
	nb_pipes = get_nb_pipes(shell);
	shell->exec.commands = ft_calloc(nb_pipes + 2, sizeof(char **));
	if (!shell->exec.commands)
		return (-1);
	shell->exec.commands[nb_pipes + 1] = NULL;
	shell->exec.redirs = ft_calloc(nb_pipes + 2, sizeof(t_redirs));
	if (!shell->exec.redirs)
		return (free(shell->exec.commands), -1);
	shell->exec.pids = ft_calloc(nb_pipes + 2, sizeof(int));
	if (!shell->exec.pids)
		return (free(shell->exec.commands), free(shell->exec.redirs), -1);
	if (init_pipes(shell, nb_pipes))
		return (-1);
	if (init_commands(shell, nb_pipes))
	{
		shell->last_exit = 1;
		return (-2);
	}
	if (get_redirs(shell, nb_pipes))
		shell->last_exit = 1;
	return (nb_pipes + 1);
}
