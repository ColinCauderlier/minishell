/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/04 11:43:41 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//En cas d'erreur, l'expand n'est pas fait
char	*get_expand(char *str, t_envp *envp)
{
	int		i;
	int		name_len;
	int		key_len;
	char	*name;

	i = 0;
	while (str[i] && !is_expand_lim(str[i]))
		i++;
	name = ft_substr(str, 0, i);
	name_len = i;
	if (!name)
		return (NULL);
	i = -1;
	while (envp && envp->next)
	{
		key_len = ft_strlen(envp->key);
		if (ft_strncmp(name, envp->key, max(name_len, key_len)) == 0)
		{
			free(name);
			name = envp->value;
			return (name);
		}
		envp = envp->next;
	}
	return (free(name), NULL);
}
