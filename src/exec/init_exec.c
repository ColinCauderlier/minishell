/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:03:00 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/11 16:13:55 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	init_pipes(t_shell *shell, int nb_pipes)
{
	int	i;

	i = 0;
	shell->exec.pipes = ft_calloc(nb_pipes + 1, sizeof(int *));
	if (!shell->exec.pipes)
		return (free(shell->exec.pids), free(shell->exec.commands), 1);
	while (i < nb_pipes)
	{
		shell->exec.pipes[i] = ft_calloc(2, sizeof(int));
		if (!shell->exec.pipes[i])
			return (free_exec(shell), 1);
		if (pipe(shell->exec.pipes[i]) == -1)
			return (free_exec(shell), 1);
		i++;
	}
	shell->exec.pipes[nb_pipes] = NULL;
	return (0);
}

static int	init_commands(t_shell *shell, int nb_pipes)
{
	int		i;
	t_token	*list;

	i = 0;
	list = shell->tokens;
	while (i < nb_pipes + 1)
	{
		shell->exec.commands[i] = get_commands(list);
		if (!shell->exec.commands[i])
			return (free_commands(shell), 1);
		while (list->next && list->token_type != PIPE)
			list = list->next;
		if (list->next && list->token_type == PIPE)
			list = list->next;
		i++;
	}
	shell->exec.commands[i] = NULL;
	return (0);
}

//Un remake de strip_token_quotes du tokenizer (get_new_content.c)
static char	*strip_delimiter_quotes(char *del)
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

static int	init_redirs(t_shell *shell, int nb_pipes)
{
	int			i;
	t_token		*list;
	t_redirs	*redir;
	char		*line;
	char		*temp;

	redir = shell->exec.redirs;
	i = 0;
	line = "";
	while (i < nb_pipes + 1)
	{
		redir[i].fname_in = NULL;
		redir[i].fname_out = NULL;
		redir[i].delimiter = NULL;
		redir[i].fd_in = -1;
		redir[i].fd_out = -1;
		i++;
	}
	redir = shell->exec.redirs;
	list = shell->tokens;
	i = 0;
	while (list)
	{
		if (list->token_type == PIPE)
			i++;
		else if (list->token_type == REDIR_OUT_WW
			|| list->token_type == REDIR_OUT_APP_MODE_WW)
		{
			if (redir[i].fd_out != -1)
				close(redir[i].fd_out);
			if (list->token_type == REDIR_OUT_WW)
				redir[i].fname_out = list->content + 1;
			else
				redir[i].fname_out = list->content + 2;
			if (list->token_type == REDIR_OUT_WW)
				redir[i].fd_out = open(redir[i].fname_out,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				redir[i].fd_out = open(redir[i].fname_out,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir[i].fd_out < 0)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
		}
		else if (list->token_type == REDIR_OUT
			|| list->token_type == REDIR_OUT_APP_MODE)
		{
			if (redir[i].fd_out != -1)
				close(redir[i].fd_out);
			redir[i].fname_out = list->next->content;
			if (list->token_type == REDIR_OUT)
				redir[i].fd_out = open(redir[i].fname_out,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				redir[i].fd_out = open(redir[i].fname_out,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (redir[i].fd_out < 0)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
		}
		else if (list->token_type == REDIR_IN_WW)
		{
			if (redir[i].fd_in != -1)
				close(redir[i].fd_in);
			redir[i].fname_in = list->content + 1;
			redir[i].fd_in = open(redir[i].fname_in, O_RDONLY);
			if (redir[i].fd_in < 0)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
		}
		else if (list->token_type == REDIR_IN)
		{
			if (redir[i].fd_in != -1)
				close(redir[i].fd_in);
			redir[i].fname_in = list->next->content;
			redir[i].fd_in = open(redir[i].fname_in, O_RDONLY);
			if (redir[i].fd_in < 0)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
		}
		else if (list->token_type == HEREDOC_WW || list->token_type == HEREDOC)
		{
			if (redir[i].fd_in != -1)
				close(redir[i].fd_in);
			if (list->token_type == HEREDOC_WW)
				redir[i].delimiter = list->content + 2;
			else
				redir[i].delimiter = list->next->content;
			if (!redir[i].delimiter)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
			redir[i].delimiter = strip_delimiter_quotes(redir[i].delimiter);
			temp = ft_itoa(i + 1);
			if (!temp)
			{
				ft_fprintf(2, "Minishell: a malloc has failed\n");
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
			redir[i].fname_in = ft_strjoin( ".", temp);
			free(temp);
			if (!redir[i].fname_in)
			{
				ft_fprintf(2, "Minishell: a malloc has failed\n");
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
			redir[i].fd_in = open(redir[i].fname_in,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redir[i].fd_in < 0)
			{
				while (list->next && list->token_type != PIPE)
					list = list->next;
				continue ;
			}
			while (1)
			{
				line = readline("> ");
				if (!line)
					break ;
				if (!list->got_quotes)
				{
					temp = expand_raw_prompt(line, shell);
					free(line);
					if (!temp)
						break ;
					line = temp;
				}
				if (ft_strncmp(line, redir[i].delimiter, ft_strlen(redir[i].delimiter) + 1) == 0)
				{
					free(line);
					break;
				}		
				ft_fprintf(redir[i].fd_in, "%s\n",line);
				free(line);
			}
			close(redir[i].fd_in);
			redir[i].fd_in = open(redir[i].fname_in, O_RDONLY);
		}
		list = list->next;
	}
	return (0);
}

int	init_exec(t_shell *shell)
{
	int	nb_pipes;

	nb_pipes = get_nb_pipes(shell);
	shell->exec.commands = ft_calloc(nb_pipes + 2, sizeof(char **));
	if (!shell->exec.commands)
		return (-1);
	shell->exec.commands[nb_pipes + 1] = NULL;
	shell->exec.redirs = ft_calloc(nb_pipes + 2, sizeof(t_redirs));
	if (!shell->exec.redirs)
		return (free(shell->exec.commands), -1);
	shell->exec.pids = ft_calloc(nb_pipes + 2, sizeof(int));
	if (!shell->exec.pids)
		return (free(shell->exec.commands), free(shell->exec.redirs), -1);
	if (init_pipes(shell, nb_pipes))
		return (-1);
	if (init_commands(shell, nb_pipes))
	{
		shell->last_exit = 1;
		return (-2);
	}
	if (init_redirs(shell, nb_pipes))
		shell->last_exit = 1;
	return (nb_pipes + 1);
}
