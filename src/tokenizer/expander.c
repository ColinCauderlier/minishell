/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/30 19:41:40 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//En cas d'erreur, l'expand n'est pas fait
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
	if (!name)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		if (ft_strncmp(name, envp[i], max(ft_strlen(name), j)) == 0)
		{
			free(name);
			equal = j;
			while (envp[i][j])
				j++;
			name = ft_substr(envp[i], equal + 1, j - equal);
			if (!name)
				return (NULL);
			return (name);
		}
	}
	free(name);
	return (NULL);
}
