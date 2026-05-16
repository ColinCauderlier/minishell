/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/16 16:46:27 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# define STX_ER_MESSAGE "minishell: syntax error near unexpected token"

//PIPE : |
//REDIR_IN : >
//REDIR_IN_WW : > + filename, ex: '<Makefile' (WW means "with word")
//REDIR_OUT : <
//REDIR_OUT_WW : < + filename, ex: '>outfile'
//HEREDOC : >>
//REDIR_OUT_APP_MODE : >>
typedef enum s_type
{
	PIPE,
	REDIR_IN,
	REDIR_IN_WW,
	REDIR_OUT,
	REDIR_OUT_WW,
	HEREDOC,
	REDIR_OUT_APP_MODE,
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
	struct s_token	*next;
}					t_token;

typedef struct s_exec
{
	char	***commands;
	int		**pipes;
	int		*pids;
}	t_exec;

typedef struct s_shell
{
	t_token			*tokens;
	t_exec			exec;
	struct termios	term_ctl;
	char			*user_input;
	char			**envp;
	bool			custom_envp;
	int				last_exit;
	int				nb_token;
}					t_shell;

#endif
