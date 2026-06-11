/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/11 19:30:13 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# define STX_ERR "minishell: syntax error near unexpected token"

// PIPE : |
// REDIR_IN : <
// REDIR_IN_WW : < + filename, ex: '<Makefile' (WW means "with word")
// REDIR_OUT : >
// REDIR_OUT_WW : > + filename, ex: '>outfile'
// HEREDOC : <<
// REDIR_OUT_APP_MODE : >>
// REDIR_OUT_APP_MODE_WW : >>
typedef enum s_type
{
	PIPE,
	REDIR_IN,
	REDIR_IN_WW,
	REDIR_OUT,
	REDIR_OUT_WW,
	HEREDOC,
	HEREDOC_WW,
	REDIR_OUT_APP_MODE,
	REDIR_OUT_APP_MODE_WW,
	WORD,
}					t_type;

typedef enum s_state
{
	GENERAL,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
}					t_state;

typedef struct s_token
{
	t_type			token_type;
	char			*content;
	int				got_quotes;
	struct s_token	*next;
}					t_token;

// tableau de s_redir NULL terminated
typedef struct s_redir
{
	char			*fname_in;
	char			*fname_out;
	int				fd_in;
	int				fd_out;
	char			*delimiter;
}					t_redirs;

typedef struct s_exec
{
	char			***commands;
	int				**pipes;
	int				*pids;
	t_redirs		*redirs;
	int				fdin_save;
	int				fdout_save;
}					t_exec;

typedef struct s_parsing
{
	int				i[2];
	t_state			state;
	int				token_index;
	char			*old;
	char			**new;
}					t_parsing;

typedef struct s_shell
{
	t_token			*tokens;
	t_exec			exec;
	struct termios	term_ctl;
	char			*user_input;
	char			**envp;
	char			**exp;
	int				last_exit;
	int				nb_token;
}					t_shell;

#endif
