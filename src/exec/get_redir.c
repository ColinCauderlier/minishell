/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 11:27:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/22 17:35:56 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int     is_redir_wi_word(t_token *tkn)
{
        if (tkn->token_type == REDIR_IN_WW || tkn->token_type == REDIR_OUT_WW)
                return (1);
        return (0);
}

int	get_len_redirs(t_token *tokens)
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


static int      init_redirs(t_shell *shell, int nb_pipes)
{
        int             i;
        t_token *list;

        i = 0;
        list = shell->tokens;
        while (i < nb_pipes + 1)
        {
                shell->exec.commands[i] = get_commands(list);
                if (!shell->exec.commands[i])
                        return (free_commands(shell), 1);
                while (list->next && list->token_type != PIPE)
                        list = list->next;
                if (list->next && list->next->token_type == PIPE)
                        list = list->next;
                i++;
        }
        shell->exec.commands[i] = NULL;
        return (0);
}

t_token	*get_redirs_loop(t_token *list, char **commands, int *i)
{
	if (list->token_type == REDIR_IN)
	{
	}
	if (list->token_type == REDIR_IN_WW)
	{

	}
	if (list->token_type == REDIR_OUT)
	{
	}
	if (list->token_type == REDIR_OUT_WW)
	{
	}
	if (list->token_type == REDIR_OUT_APP_MODE)
	{
	}
	if (list->token_type == REDIR_OUT_APP_MODE_WW)
	{
	}
	if (list->next)
		list = list->next;
	return (list);
}

char	**get_redirs(t_token *tokens)
{
	t_token	*list;
	int		i;
	char	**redirs;

	i = 0;
	list = tokens;
	redirs = malloc((get_len_redirs(list) + 1) * sizeof(char *));
	if (!redirs)
		return (NULL);
	while (list && list->token_type != PIPE)
	{
		list = redirs_loop(list, redirs, &i);
		if (!list)
			return (NULL);
	}
	redirs[i] = NULL;
	return (redirs);
}
