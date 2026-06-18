/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 16:49:29 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/18 17:16:48 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	setup_signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	free_previous_infile(t_redirs *redir)
{
	if (redir->fname_in)
		free(redir->fname_in);
	if (redir->delimiter)
		free(redir->delimiter);
}

void	get_delimiter(t_token *list, t_redirs *redir)
{
	if (list->token_type == HEREDOC_WW)
		redir->delimiter = list->content + 2;
	else
		redir->delimiter = list->next->content;
	redir->delimiter = strip_delimiter_quotes(redir->delimiter);
}
