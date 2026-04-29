/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:39:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 16:19:35 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	expand_case(char *old, int *i, char **new, char **envp)
{
	char	*join;

	if (!old[*i + 1] || is_expand_lim(old[*i + 1]))
	{
		join = ft_strjoin(*new, "$");
		free(*new);
		*new = join;
	}
	*new = ft_strappend(*new, get_expand(&old[*i + 1], envp));
	(*i)++;
	while (old[*i] && !is_expand_lim(old[*i]))
		(*i)++;
	return (*i);
}

static char	*new_content_loop(char *old, char **envp, char *new)
{
	int		start;
	int		i;
	t_state	state;

	i = 0;
	state = GENERAL;
	start = 0;
	while (old[i])
	{
		if (change_state(old[i], &state))
		{
			new = ft_strappend(new, ft_substr(old, start, i - start));
			start = ++i;
		}
		else if (state != SIMPLE_QUOTE && old[i] == '$')
		{
			new = ft_strappend(new, ft_substr(old, start, i - start));
			start = expand_case(old, &i, &new, envp);
		}
		else
			i++;
	}
	new = ft_strappend(new, ft_substr(old, start, i - start));
	return (new);
}

int	get_new_content(t_token *tkn, char **envp)
{
	char	*new;

	new = malloc((1) * sizeof(char));
	if (!new)
		return (0);
	new[0] = '\0';
	new = new_content_loop(tkn->content, envp, new);
	if (!new)
		return (0);
	free(tkn->content);
	tkn->content = new;
	return (1);
}
