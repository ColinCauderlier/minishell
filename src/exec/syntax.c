/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:14:39 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:21:41 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	is_redir_wo_word(t_token *tkn)
{
	if (tkn->token_type == REDIR_IN || tkn->token_type == REDIR_OUT)
		return (1);
	if (tkn->token_type == HEREDOC || tkn->token_type == REDIR_OUT_APP_MODE)
		return (1);
	return (0);
}

static int	with_word_case(t_token *list)
{
	size_t	i;
	int		charac_bool;
	char	mess[2];

	i = 0;
	charac_bool = 1;
	while (list->content[i] && charac_bool)
	{
		if (!is_redir_symbol(list->content[i]))
		{
			i--;
			charac_bool = 0;
		}
		i++;
	}
	if (i == ft_strlen(list->content))
	{
		mess[0] = list->content[0];
		if (list->content[1] == mess[0])
			mess[1] = list->content[1];
		else
			mess[1] = '\0';
		return (ft_fprintf(2, "%s `%s'\n", STX_ERR, mess), 2);
	}
	return (0);
}

static int	check_syntax_redir(t_shell *shell)
{
	t_token	*list;

	list = shell->tokens;
	while (list && list->next)
	{
		if (list->token_type == REDIR_IN_WW || list->token_type == REDIR_OUT_WW)
		{
			if (with_word_case(list) == 2)
				return (2);
		}
		if (is_redir_wo_word(list) || ft_strncmp(list->content, "<>", 3) == 0)
		{
			if (!list->next || !list->next->content)
				return (ft_fprintf(2, "%s `newline'\n", STX_ERR), 2);
			if (list->next->token_type != WORD)
			{
				ft_fprintf(2, "%s `%s'\n", STX_ERR, list->next->content);
				return (2);
			}
		}
		list = list->next;
	}
	return (0);
}

static int	check_syntax_pipes(t_shell *shell)
{
	t_token	*list;

	list = shell->tokens;
	if (list->token_type == PIPE)
		return (ft_fprintf(2, "%s `|'\n", STX_ERR), 2);
	while (list && list->next)
	{
		if (list->token_type == PIPE)
		{
			if (!list->next->content)
				return (ft_fprintf(2, "%s `newline'\n", STX_ERR), 2);
			if (list->next->token_type == PIPE)
				return (ft_fprintf(2, "%s `|'\n", STX_ERR), 2);
		}
		list = list->next;
	}
	return (0);
}

int	check_syntax_shell(t_shell *shell)
{
	int	status;

	status = check_syntax_pipes(shell);
	if (status)
		return (status);
	status = check_syntax_redir(shell);
	if (status)
		return (status);
	return (0);
}
