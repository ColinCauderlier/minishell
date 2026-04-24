/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/24 15:10:19 by lucinguy         ###   ########.fr       */
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


