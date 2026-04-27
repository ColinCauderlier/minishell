/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:25:48 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/27 12:29:48 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_OUT_APP_MODE,
	WORD,
} t_type;

typedef enum
{
	GENERAL,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
} t_state;

typedef struct s_token
{
	t_type			token_type;
	t_state			token_state;
	char			*content;
	struct s_token	*next;
}	t_token;

#endif
