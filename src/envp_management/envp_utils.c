/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 16:22:39 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/02 16:22:47 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

t_envp	*create_envp_node(char *key, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (free(node), NULL);
	node->value = ft_strdup(value);
	if (!node->value)
		return (free(node->key), free(node), NULL);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	envp_add_back(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

int	parse_env_var(char *env_var, char **key, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(env_var, '=');
	if (!equal_pos)
		return (0);
	*key = ft_substr(env_var, 0, equal_pos - env_var);
	if (!*key)
		return (0);
	*value = ft_strdup(equal_pos + 1);
	if (!*value)
		return (free(*key), 0);
	return (1);
}

void	free_envp_list(t_envp **envp)
{
	t_envp	*next;

	while (envp && *envp)
	{
		next = (*envp)->next;
		free((*envp)->key);
		free((*envp)->value);
		free(*envp);
		*envp = next;
	}
}

int	append_envp_entry(t_shell *shell, char *key, char *value)
{
	t_envp	*node;

	node = create_envp_node(key, value);
	if (!node)
		return (0);
	envp_add_back(&shell->envp, node);
	return (1);
}
