/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:39:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/11 14:39:12 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

char	*append_word(t_parsing *prs, char **new)
{
	char	*tmp;

	tmp = ft_substr(prs->old, prs->i[0], prs->i[1] - prs->i[0]);
	if (!tmp)
		return (NULL);
	*new = ft_strappend(*new, tmp);
	return (*new);
}

static int	inside_loop_expand(t_parsing *prs, t_shell *shell, char **new)
{
	if (change_state(prs->old[prs->i[1]], &(prs->state)))
	{
		(prs->i[1])++;
		*new = append_word(prs, new);
		if (!*new)
			return (-1);
		prs->i[0] = (prs->i[1]);
	}
	else if (prs->state != SIMPLE_QUOTE && prs->old[prs->i[1]] == '$')
	{
		*new = append_word(prs, new);
		if (!*new)
			return (-1);
		prs->i[0] = expand(prs, new, shell);
		if (prs->i[0] == -1)
			return (free(*new), -1);
	}
	else
		(prs->i[1])++;
	return (0);
}

// I need 2 index, the start and the end of every str I will not expand
// i[0] is the start, i[1] the end
int	inside_loop_strip(t_parsing *prs, char **new)
{
	if (change_state(prs->old[prs->i[1]], &(prs->state)))
	{
		*new = append_word(prs, new);
		if (!*new)
			return (-1);
		prs->i[0] = ++(prs->i[1]);
	}
	else
		(prs->i[1])++;
	return (0);
}

// Expand the raw prompt string before tokenization
char	*expand_raw_prompt(char *prompt, t_shell *shell)
{
	char		*new;
	t_parsing	prs;

	new = NULL;
	prs.old = prompt;
	prs.i[0] = 0;
	prs.i[1] = 0;
	prs.state = GENERAL;
	while (prs.old[prs.i[1]])
	{
		if (inside_loop_expand(&prs, shell, &new) == -1)
			return (NULL);
	}
	new = append_word(&prs, &new);
	return (new);
}

// Strip quotes from an existing token
int	strip_token_quotes(t_token *list)
{
	char		*new;
	t_parsing	prs;

	new = NULL;
	prs.old = list->content;
	prs.i[0] = 0;
	prs.i[1] = 0;
	prs.state = GENERAL;
	while (prs.old[prs.i[1]])
	{
		if (inside_loop_strip(&prs, &new) == -1)
			return (0);
	}
	new = append_word(&prs, &new);
	if (!new)
		return (0);
	if (ft_strlen(new) != ft_strlen(prs.old))
		list->got_quotes = 1;
	free(list->content);
	list->content = new;
	return (1);
}
