/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 14:34:19 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/08 16:07:21 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//En cas d'erreur, l'expand n'est pas fait
char	*get_expand(char *str, t_shell *shell)
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
	while (shell->envp)
	{
		key_len = ft_strlen(shell->envp->key);
		if (ft_strncmp(name, shell->envp->key, max(name_len, key_len)) == 0)
			return (free(name), ft_strdup(shell->envp->value));
		shell->envp = shell->envp->next;
	}
	return (free(name), ft_strdup(""));
}
