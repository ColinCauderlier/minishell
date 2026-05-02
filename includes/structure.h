/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/02 13:54:29 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum s_type
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
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

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

typedef struct s_shell
{
	t_envp			*envp;
	t_token			*tokens;
	char			*user_input;
	int				last_exit;
}					t_shell;
#endif
