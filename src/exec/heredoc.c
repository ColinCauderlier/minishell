/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:12:03 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/18 16:32:58 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int			g_signal = 0;

static void	get_delimiter(t_token *list, t_redirs *redir)
{
	if (list->token_type == HEREDOC_WW)
		redir->delimiter = list->content + 2;
	else
		redir->delimiter = list->next->content;
	redir->delimiter = strip_delimiter_quotes(redir->delimiter);
}

void	heredoc_loop(t_shell *shell, t_token *list, t_redirs redir, char *line)
{
	char	*temp;

	temp = NULL;
	setup_signal_heredoc();
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT || g_signal == SIGQUIT)
			break ;
		if (!line)
		{
			ft_fprintf(2,
				"minishell: warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (!list->got_quotes)
		{
			temp = expand_raw_prompt(line, shell);
			free(line);
			if (!temp)
				break ;
			line = temp;
		}
		if (ft_strncmp(line, redir.delimiter, ft_strlen(redir.delimiter)
				+ 1) == 0)
		{
			free(line);
			break ;
		}
		ft_fprintf(redir.fd_in, "%s\n", line);
		free(line);
	}
}

void	free_previous_infile(t_redirs *redir)
{
	if (redir->fname_in)
		free(redir->fname_in);
	if (redir->delimiter)
		free(redir->delimiter);
}

t_token	*heredoc(t_redirs *redir, t_shell *shell, t_token *list, int i)
{
	char	*temp;
	int		saved_stdin;

	if (redir->fd_in != -1)
		close(redir->fd_in);
	free_previous_infile(redir);
	get_delimiter(list, redir);
	if (!redir->delimiter)
		return (goto_next_command(list, 1));
	temp = ft_itoa(i + 1);
	if (!temp)
		return (goto_next_command(list, 1));
	redir->fname_in = ft_strjoin(".", temp);
	free(temp);
	if (!redir->fname_in)
		return (goto_next_command(list, 1));
	redir->fd_in = open(redir->fname_in, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (redir->fd_in < 0)
		return (goto_next_command(list, 1));
	saved_stdin = dup(STDIN_FILENO);
	heredoc_loop(shell, list, *redir, "");
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(redir->fd_in);
	redir->fd_in = open(redir->fname_in, O_RDONLY);
	return (list);
}
void	setup_signal_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
