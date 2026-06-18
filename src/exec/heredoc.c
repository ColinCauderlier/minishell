/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:12:03 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/18 17:20:45 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int			g_signal = 0;

void	heredoc_expand(t_shell *shell, char **line)
{
	char	*temp;

	temp = expand_raw_prompt(*line, shell);
	free(*line);
	*line = temp;
}

void	heredoc_loop(t_shell *shell, t_token *list, t_redirs redir, char *line)
{
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_fprintf(2, HERE_ERR);
			break ;
		}
		if (!list->got_quotes)
			heredoc_expand(shell, &line);
		if (!line)
			break ;
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

void	end_heredoc(t_shell *shell, t_token *list, t_redirs *redir)
{
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	setup_signal_heredoc();
	heredoc_loop(shell, list, *redir, "");
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(redir->fd_in);
	redir->fd_in = open(redir->fname_in, O_RDONLY);
}

t_token	*heredoc(t_redirs *redir, t_shell *shell, t_token *list, int i)
{
	char	*temp;

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
	end_heredoc(shell, list, redir);
	return (list);
}
