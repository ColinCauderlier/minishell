/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:39:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/18 14:47:20 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	*append_word(t_parsing *prs, char **new)
{
	char	*tmp;

	tmp = ft_substr(prs->old, prs->i[0], prs->i[1] - prs->i[0]);
	if (!tmp)
		return (NULL);
	*new = ft_strappend(*new, tmp);
	return (*new);
}

static int	inside_loop(t_parsing *prs, t_shell *shell, char **new)
{
	if (change_state(prs->old[prs->i[1]], &(prs->state)))
	{
		*new = append_word(prs, new);
		if (!*new)
			return (-1);
		prs->i[0] = ++(prs->i[1]);
	}
	else if (prs->state != SIMPLE_QUOTE && prs->old[prs->i[1]] == '$')
	{
		*new = append_word(prs, new);
		if (!*new)
			return (-1);
		prs->i[0] = expand(prs->old, &(prs->i[1]), new, shell);
		if (prs->i[0] == -1)
			return (free(*new), -1);
	}
	else
		(prs->i[1])++;
	return (0);
}

//I need 2 index, the start and the end of every str I will not expand
//i[0] is the start, i[1] the end
static int	new_content_loop(t_parsing *prs, t_shell *shell, char **new)
{
	prs->i[0] = 0;
	prs->i[1] = 0;
	prs->state = GENERAL;
	while (prs->old[prs->i[1]])
	{
		if (inside_loop(prs, shell, new) == -1)
			return (-1);
	}
	*new = append_word(prs, new);
	if (!new)
		return (-1);
	return (0);
}

int	get_new_content(t_token *list, t_shell *shell)
{
	char		*new;
	t_parsing	prs;

	new = NULL;
	prs.old = list->content;
	new_content_loop(&prs, shell, &new);
	if (!new)
		return (0);
	free(list->content);
	list->content = new;
	return (1);
}
