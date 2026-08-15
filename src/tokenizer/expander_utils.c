/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:12:20 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/12 16:27:42 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	get_new_len(const char *str)
{
	int	i;
	int	len;
	int	in_word;

	i = 0;
	len = 0;
	in_word = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && in_word == 1)
		{
			in_word = 0;
			len++;
		}
		if (!ft_isspace(str[i]))
		{
			in_word = 1;
			len++;
		}
		i++;
	}
	len++;
	return (len);
}

char	*trim_spaces(char *str, int i, int j)
{
	char	*res;
	int		in_word;
	int		len;

	in_word = 0;
	len = get_new_len(str);
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i] && j < len - 1)
	{
		if (!ft_isspace(str[i]))
		{
			in_word = 1;
			res[j] = str[i];
			j++;
		}
		if (ft_isspace(str[i]) && in_word == 1)
		{
			res[j] = ' ';
			j++;
			in_word = 0;
		}
		i++;
	}
	res[j] = '\0';
	return (free(str), res);
}

// En cas d'erreur, l'expand n'est pas fait
char	*get_expand(char *str, char **envp)
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
