/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 15:42:03 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	get_all_types(t_token *lst)
{
	if (!lst)
		return ;
	while (lst && lst->next)
	{
		if (ft_strncmp(lst->content, "|\0", 2) == 0)
			lst->token_type = PIPE;
		else if (ft_strncmp(lst->content, "<\0", 2) == 0)
			lst->token_type = REDIR_IN;
		else if (ft_strncmp(lst->content, ">\0", 2) == 0)
			lst->token_type = REDIR_OUT;
		else if (ft_strncmp(lst->content, "<<\0", 3) == 0)
			lst->token_type = HEREDOC;
		else if (ft_strncmp(lst->content, ">>\0", 3) == 0)
			lst->token_type = REDIR_OUT_APP_MODE;
		else
			lst->token_type = WORD;
		lst = lst->next;
	}
}

//Retourne s'il y a eu un changement d'etat ou non
int	change_state(char c, t_state *state)
{
	if (c == '\'' && *state == GENERAL)
	{
		*state = SIMPLE_QUOTE;
		return (1);
	}
	else if (c == '\"' && *state == GENERAL)
	{
		*state = DOUBLE_QUOTE;
		return (1);
	}
	else if (c == '\'' && *state == SIMPLE_QUOTE)
	{
		*state = GENERAL;
		return (1);
	}
	else if (c == '\"' && *state == DOUBLE_QUOTE)
	{
		*state = GENERAL;
		return (1);
	}
	return (0);
}

//Recupere le contenu brut des tokens 
//et remplace le contenu par une autre chaine 
//dans laquelle les guillemets et les expand ont ete geres
void	tokenize(char *prompt, char **envp)
{
	t_token		*list;
	t_token		*head;

	list = get_content(prompt);
	head = list;
	while (list && list->next)
	{
		if (!get_new_content(list, envp))
			return ;
		list = list->next;
	}
	list = head;
	get_all_types(list);
	while (list && list->next)
	{
		printf("%s %s\n", list->content, get_type(*list));
		list = list->next;
	}
	free_all_tokens(head);
	free(head);
}
