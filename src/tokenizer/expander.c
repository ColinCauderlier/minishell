/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/11 16:54:25 by ccauderl         ###   ########.fr       */
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
