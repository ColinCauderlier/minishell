/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:05:10 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 15:02:55 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//Un remake de strip_token_quotes du tokenizer (get_new_content.c)
char	*strip_delimiter_quotes(char *del)
{
	t_parsing	prs;
	char		*new;

	new = NULL;
	prs.old = del;
	prs.i[0] = 0;
	prs.i[1] = 0;
	prs.state = GENERAL;
	while (prs.old[prs.i[1]])
	{
		if (inside_loop_strip(&prs, &new) == -1)
			return (NULL);
	}
	new = append_word(&prs, &new);
	return (new);
}

//In case of an error during redirections, go to the next command
t_token	*goto_next_command(t_token *list, int bool_message)
{
	if (bool_message)
		ft_fprintf(2, "Minishell: a malloc has failed\n");
	while (list->next && list->token_type != PIPE)
		list = list->next;
	return (list);
}

int	is_redir_wo_word(t_token *tkn)
{
	if (tkn->token_type == RED_IN || tkn->token_type == RED_OUT)
		return (1);
	if (tkn->token_type == HEREDOC || tkn->token_type == RED_OUT_APP_MODE)
		return (1);
	return (0);
}

int	is_redir_ww(t_token *tkn)
{
	if (tkn->token_type == RED_IN_WW || tkn->token_type == RED_OUT_WW)
		return (1);
	if (tkn->token_type == HEREDOC_WW || tkn->token_type == RED_OUT_APP_MODE_WW)
		return (1);
	return (0);
}
