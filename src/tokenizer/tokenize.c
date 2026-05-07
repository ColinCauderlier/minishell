/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:44:46 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/07 17:21:00 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//Lexer, associe le type du token a ce dernier
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

//Change l'etat actuel lors du parsing du token
//Retourne 1 s'il y a eu un changement d'etat, 0 sinon
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

int	count_nb_token(t_token *list)
{
	int	count;

	count = 0;
	while (list->content)
	{
		count++;
		list = list->next;
	}
	return (count);
}

//Recupere le contenu brut des tokens 
//et remplace le contenu par une autre chaine 
//dans laquelle les guillemets et les expand ont ete geres
//Retourne 1 si jamais c'est alloue mais qu'il y a eu un soucis de malloc 
//lors de la tokenization
//Retourne 2 si jamais le premier malloc ne passe pas
//La derniere boucle affiche les tokens
int	tokenize(char *prompt, t_shell *shell)
{
	t_token		*list;

	list = get_content(prompt);
	if (!list)
		return (2);
	shell->tokens = list;
	while (list && list->content)
	{
		if (!get_new_content(list, shell))
			return (1);
		list = list->next;
	}
	list = shell->tokens;
	get_all_types(list);
	shell->nb_token = count_nb_token(list);
	while (list && list->next)
	{
		printf("%s %s\n", list->content, get_type(*list));
		list = list->next;
	}
	return (0);
}
