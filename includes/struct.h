/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/24 17:17:23 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum {
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_OUT_APP_MODE,
	WORD,
} type;

typedef enum {
	GENERAL,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
} state;

typedef struct s_token {
	type			token_type;
	state			token_state;
	char			*content;
	struct s_token	*next;
} t_token;
