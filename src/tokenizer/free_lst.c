/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:49:38 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/30 18:28:23 by ccauderl         ###   ########.fr       */
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

//detruit la liste jusqu'a la position pos_res
void	free_res(t_token *res, int pos_res)
{
	while (pos_res > -1)
		ft_tokendelone(&res[pos_res--]);
	free(res);
}

//free la liste de tokens et leurs contenus
void	free_all_tokens(t_shell *shell)
{
	t_token	*head;

	head = shell->tokens;
	while (shell->tokens && shell->tokens->next)
	{
		free(shell->tokens->content);
		shell->tokens = shell->tokens->next;
	}
	free(head);
}
