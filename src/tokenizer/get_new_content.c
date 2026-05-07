/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:39:11 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/07 17:17:58 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	expand_case(char *old, int *i, char **new, t_shell *shell)
{
	char	*join;
	char	*itoa;

	if (!old[*i + 1] || ft_isspace(old[*i + 1]))
	{
		join = ft_strjoin(*new, "$");
		if (!join)
			return (-1);
		free(*new);
		*new = join;
	}
	else if (old[*i + 1] == '?')
	{
		itoa = ft_itoa(shell->last_exit);
		if (!itoa)
			return (-1);
		join = ft_strjoin(*new, itoa);
		if (!join)
			return (-1);
		free(*new);
		free(itoa);
		*new = join;
	}
	else
		*new = ft_strappend(*new, get_expand(&old[*i + 1], shell->envp));
	if (!(*new))
		return (-1);
	(*i)++;
	while (old[*i] && !is_expand_lim(old[*i]))
		(*i)++;
	return (*i);
}

static char	*new_content_loop(char *old, t_shell *shell, char *new)
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
			if (!new)
				return (NULL);
			start = ++i;
		}
		else if (state != SIMPLE_QUOTE && old[i] == '$')
		{
			new = ft_strappend(new, ft_substr(old, start, i - start));
			if (!new)
				return (NULL);
			start = expand_case(old, &i, &new, shell);
			if (i == -1)
				return (free(new), NULL);
		}
		else
			i++;
	}
	new = ft_strappend(new, ft_substr(old, start, i - start));
	if (!new)
		return (NULL);
	return (new);
}

int	get_new_content(t_token *list, t_shell *shell)
{
	char	*new;

	new = malloc((1) * sizeof(char));
	if (!new)
		return (0);
	new[0] = '\0';
	new = new_content_loop(list->content, shell, new);
	if (!new)
		return (0);
	free(list->content);
	list->content = new;
	return (1);
}
