/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:49:05 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 14:53:20 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fichier temporaire, sert au debug
#include "../../includes/includes.h"

static char	*get_type(t_token token)
{
	char	*str;

	str = NULL;
	if (token.token_type == PIPE)
		str = "PIPE";
	else if (token.token_type == RED_IN)
		str = "REDIR_IN";
	else if (token.token_type == RED_OUT)
		str = "REDIR_OUT";
	else if (token.token_type == HEREDOC)
		str = "HEREDOC";
	else if (token.token_type == HEREDOC_WW)
		str = "HEREDOC_WW";
	else if (token.token_type == RED_OUT_APP_MODE)
		str = "REDIR_OUT_APP_MODE";
	else if (token.token_type == RED_OUT_APP_MODE_WW)
		str = "REDIR_OUT_APP_MODE_WW";
	else if (token.token_type == WORD)
		str = "WORD";
	else if (token.token_type == RED_IN_WW)
		str = "REDIR_IN_WW";
	else if (token.token_type == RED_OUT_WW)
		str = "REDIR_OUT_WW";
	return (str);
}

void	print_tokens(t_shell *shell)
{
	t_token	*list;

	list = shell->tokens;
	while (list && list->next)
	{
		printf("%s %s\n", list->content, get_type(*list));
		list = list->next;
	}
}
