/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:49:38 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 14:25:52 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	ft_tokendelone(t_token *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	lst->content = NULL;
}

void	free_res(t_token *res, int pos_res)
{
	while (pos_res > -1)
		ft_tokendelone(&res[pos_res--]);
	free(res);
}

void	free_all_tokens(t_token *tokens)
{
	while (tokens && tokens->next)
	{
		free(tokens->content);
		tokens = tokens->next;
	}
}
