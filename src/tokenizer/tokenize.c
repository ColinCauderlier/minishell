/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/27 15:04:49 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void    get_type(t_token *lst)
{
	if (!lst)
		return ;
	while (lst && lst->next)
	{
		if (ft_strncmp(lst->content, "|\0", 2) == 0)
			lst->token_type = PIPE;
		else if (ft_strncmp(lst->content, "<\0", 2) == 0)
			lst->token_type = REDIR_IN;
		else if (ft_strncmp(lst->content, ">\0", 2) == 0)
			lst->token_type = REDIR_OUT;
		else if (ft_strncmp(lst->content, "<<\0", 3) == 0)
			lst->token_type = HEREDOC;
		else if (ft_strncmp(lst->content, ">>\0", 3) == 0)
			lst->token_type = REDIR_OUT_APP_MODE;
		else
			lst->token_type = WORD;
		lst = lst->next;
	}
}

void	tokenize(char *prompt)
{
	t_token		*list;
	char		*strstate;
	char		*str;

	list = get_content(prompt);
	get_type(list);
	while (list && list->next)
	{
		if (list->token_state == GENERAL)
			strstate = "GENERAL";
		if (list->token_state == SIMPLE_QUOTE)
			strstate = "SIMPLE_QUOTE";
		if (list->token_state == DOUBLE_QUOTE)
			strstate = "DOUBLE_QUOTE";
		if (list->token_type == PIPE)
			 str = "PIPE";
		else if (list->token_type == REDIR_IN)
			str = "REDIR_IN";
		else if (list->token_type == REDIR_OUT)
			str = "REDIR_OUT";
		else if (list->token_type == HEREDOC)
			str = "HEREDOC";
		else if (list->token_type == REDIR_OUT_APP_MODE)
			str = "REDIR_OUT_APP_MODE";
		else if (list->token_type == WORD)
			str = "WORD";
		printf("%s %s %s\n", list->content, strstate, str);
		list = list->next;
	}
}
