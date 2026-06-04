/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 11:27:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:31 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	get_nb_pipes(t_shell *shell)
{
	int		count;
	t_token	*list;

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

int	get_len_command(t_token *tokens)
{
	int		len_command;
	t_token	*list;

	len_command = 0;
	list = tokens;
	while (list && list->token_type != PIPE)
	{
		if (list && list->next && is_redir_wo_word(list))
		{
			list = list->next;
			if (list->next)
				list = list->next;
		}
		if (list->token_type == WORD)
			len_command++;
		if (list->next)
			list = list->next;
	}
	return (len_command);
}

static t_token	*free_error_commands(char ***commands, int i)
{
	i--;
	while (i >= 0)
	{
		free(*(commands[i]));
		i--;
	}
	return (NULL);
}

t_token	*get_commands_loop(t_token *list, char **commands, int *i)
{
	if (is_redir_wo_word(list))
	{
		if (list->next)
			list = list->next;
		if (list->next)
			list = list->next;
	}
	else if (list->token_type == WORD)
	{
		commands[*i] = ft_strdup(list->content);
		if (!commands[*i])
			return (free_error_commands(&commands, *i));
		(*i)++;
	}
	return (list->next);
}

char	**get_commands(t_token *tokens)
{
	t_token	*list;
	int		i;
	char	**commands;

	i = 0;
	list = tokens;
	commands = malloc((get_len_command(list) + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	while (list && list->token_type != PIPE)
		list = get_commands_loop(list, commands, &i);
	commands[i] = NULL;
	return (commands);
}
