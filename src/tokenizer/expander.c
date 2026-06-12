/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 16:28:22 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	expand_last_exit(t_shell *shell, char **new)
{
	char	*itoa;
	char	*join;

	itoa = ft_itoa(shell->last_exit);
	if (!itoa)
		return (-1);
	join = ft_strjoin(*new, itoa);
	if (!join)
		return (free(itoa), (-1));
	free(*new);
	free(itoa);
	*new = join;
	return (0);
}

static int	expand_single_char(char **new, char *old, int *i)
{
	char	*join;

	if (!old[*i + 1] || ft_isspace(old[*i + 1]) || old[*i + 1] == '\"')
	{
		join = ft_strjoin(*new, "$");
		if (!join)
			return (-1);
		free(*new);
		*new = join;
	}
	return (0);
}

static int	expand_env(t_parsing *prs, char **new, t_shell *shell)
{
	char	*join;

	join = get_expand(&(prs->old[prs->i[1] + 1]), shell->envp);
	if (!join)
		return (-1);
	if (prs->state == GENERAL)
	{
		join = trim_spaces(join, 0, 0);
		if (!join)
			return (-1);
	}
	*new = ft_strappend(*new, join);
	return (0);
}

static int	expand_cases(t_parsing *prs, char **new, t_shell *shell)
{
	int		bo;

	bo = 0;
	if (expand_single_char(new, prs->old, &(prs->i[1])) == -1)
		return (-1);
	else if (prs->old[prs->i[1] + 1] == '?')
	{
		bo = 1;
		if (expand_last_exit(shell, new) == -1)
			return (-1);
	}
	else
	{
		if (expand_env(prs, new, shell) == -1)
			return (-1);
	}
	if (!(*new))
		return (-1);
	(prs->i[1])++;
	return (bo);
}

// bo: boolean to check if it is the $? case
int	expand(t_parsing *prs, char **new, t_shell *shell)
{
	int	bo;
	int	*i;

	i = &(prs->i[1]);
	bo = expand_cases(prs, new, shell);
	if (bo == -1)
		return (-1);
	if (bo == 1)
		(*i)++;
	else
	{
		while (prs->old[*i] && !is_expand_lim(prs->old[*i]))
			(*i)++;
	}
	return (*i);
}
