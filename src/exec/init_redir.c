/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 12:50:57 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 14:55:14 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	init_redirs(t_shell *shell, int nb_pipes)
{
	int			i;
	t_redirs	*redir;

	redir = shell->exec.redirs;
	i = 0;
	while (i < nb_pipes + 1)
	{
		redir[i].fname_in = NULL;
		redir[i].fname_out = NULL;
		redir[i].delimiter = NULL;
		redir[i].fd_in = -1;
		redir[i].fd_out = -1;
		i++;
	}
}

static t_token	*redir_out_ww(t_redirs redir, t_token *list)
{
	if (redir.fd_out != -1)
		close(redir.fd_out);
	if (list->token_type == RED_OUT_WW)
		redir.fname_out = ft_strdup(list->content + 1);
	else
		redir.fname_out = ft_strdup(list->content + 2);
	if (!redir.fname_out)
		return (goto_next_command(list, 1));
	if (list->token_type == RED_OUT_WW)
	{
		redir.fd_out = open(redir.fname_out,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		redir.fd_out = open(redir.fname_out,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (redir.fd_out < 0)
		return (goto_next_command(list, 0));
	return (list);
}

static t_token	*redir_out(t_redirs redir, t_token *list)
{
	if (redir.fd_out != -1)
		close(redir.fd_out);
	redir.fname_out = ft_strdup(list->next->content);
	if (!redir.fname_out)
		return (goto_next_command(list, 1));
	if (list->token_type == RED_OUT)
		redir.fd_out = open(redir.fname_out,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		redir.fd_out = open(redir.fname_out,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir.fd_out < 0)
		return (goto_next_command(list, 0));
	return (list);
}

static t_token	*redir_in(t_redirs redir, t_token *list)
{
	if (redir.fd_in != -1)
		close(redir.fd_in);
	if (list->token_type == RED_IN_WW)
		redir.fname_in = ft_strdup(list->content + 1);
	else
		redir.fname_in = ft_strdup(list->next->content);
	if (!redir.fname_in)
		return (goto_next_command(list, 1));
	redir.fd_in = open(redir.fname_in, O_RDONLY);
	if (redir.fd_in < 0)
		return (goto_next_command(list, 0));
	return (list);
}

int	get_redirs(t_shell *shell, int nb_pipes)
{
	int			i;
	t_token		*list;
	t_redirs	*redir;

	init_redirs(shell, nb_pipes);
	redir = shell->exec.redirs;
	list = shell->tokens;
	i = 0;
	while (list)
	{
		if (list->token_type == PIPE)
			i++;
		else if (list->token_type == RED_OUT_WW
			|| list->token_type == RED_OUT_APP_MODE_WW)
			list = redir_out_ww(redir[i], list);
		else if (list->token_type == RED_OUT
			|| list->token_type == RED_OUT_APP_MODE)
			list = redir_out(redir[i], list);
		else if (list->token_type == RED_IN_WW || list->token_type == RED_IN)
			list = redir_in(redir[i], list);
		else if (list->token_type == HEREDOC_WW || list->token_type == HEREDOC)
			list = heredoc(redir[i], shell, list, i);
		list = list->next;
	}
	return (0);
}
