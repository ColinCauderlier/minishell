/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:49:05 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/11 15:30:19 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Fichier temporaire, sert au debug
#include "../../includes/includes.h"

char	*get_type(t_token token)
{
	char	*str;

	if (token.token_type == PIPE)
		str = "PIPE";
	else if (token.token_type == REDIR_IN)
		str = "REDIR_IN";
	else if (token.token_type == REDIR_OUT)
		str = "REDIR_OUT";
	else if (token.token_type == HEREDOC)
		str = "HEREDOC";
	else if (token.token_type == REDIR_OUT_APP_MODE)
		str = "REDIR_OUT_APP_MODE";
	else if (token.token_type == WORD)
		str = "WORD";
	else if (token.token_type == REDIR_IN_WW)
		str = "REDIR_IN_WW";
	else if (token.token_type == REDIR_OUT_WW)
		str = "REDIR_OUT_WW";
	return (str);
}
