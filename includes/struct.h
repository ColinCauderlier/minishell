/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/23 16:57:38 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_token {
	type	token_type;
	char	*content;
	t_token	*next;
} t_token;

typedef enum {
	OPEN_PARENS;
	CLOSING_PARENS;
	SIMPLE_QUOTE;
	DOUBLE_QUOTE;
	PIPE;
	REDIR_IN;
	REDIR_OUT;
	COMMAND;
	FLAG;
	DOLLAR;
} type;


