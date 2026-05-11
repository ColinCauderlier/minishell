/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 17:14:39 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/11 17:52:09 by ccauderl         ###   ########.fr       */
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

static int	check_syntax_redir(t_shell *shell)
{
	t_token	*list;

	list = shell->tokens;
	while (list && list->next)
	{
		if (is_redir_wo_word(list))
		{
			if (!list->next || !list->next->content)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			if (list->next->token_type != WORD)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n", list->next->content);
				return (1);
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
	while (list && list->next)
	{
		if (list->token_type == PIPE)
		{
			if (!list->next)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			if (list->next->token_type == PIPE)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	check_syntax_shell(t_shell *shell)
{
	if (check_syntax_pipes(shell))
		return (1);
	if (check_syntax_redir(shell))
		return (1);
	return (0);
}
