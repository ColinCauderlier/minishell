/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/29 15:36:05 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//En cas d'erreur, l'expand n'est pas fait
static char	*get_expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		equal;
	char	*name;

	i = 0;
	while (str[i] && !is_expand_lim(str[i]))
		i++;
	name = ft_substr(str, 0, i);
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		if (ft_strncmp(name, envp[i], max(ft_strlen(name), j)) == 0)
		{
			equal = j;
			while (envp[i][j])
				j++;
			return (free(name), ft_substr(envp[i], equal + 1, j - equal));
		}
	}
	return (free(name), ft_strdup(""));
}

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

static int	expand_cases(t_parsing *prs, char **new, t_shell *shell)
{
	char	*join;
	char	*tmp;
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
		join = get_expand(&(prs->old[prs->i[1] + 1]), shell->envp);
		if (!join)
			return (-1);
		if (prs->state == GENERAL)
		{
			tmp = ft_strtrim(join, "\t\n\v\r\f ");
			free(join);
			join = malloc(ft_strlen(tmp) * sizeof(char));
			if (!join)
				return (-1);
			join = tmp;
		}
		*new = ft_strappend(*new, join);
	}
	if (!(*new))
		return (-1);
	(prs->i[1])++;
	return (bo);
}

//bo: boolean to check if it is the $? case
int	expand(t_parsing *prs, char **new, t_shell *shell)
{
	int	bo;
	int *i;

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
