/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:42:56 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/02 16:33:34 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	append_custom_envp(t_shell *shell, char *cwd)
{
	if (!append_envp_entry(shell, "HOME", cwd))
		return (0);
	if (!append_envp_entry(shell, "PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"))
		return (0);
	if (!append_envp_entry(shell, "PWD", cwd))
		return (0);
	if (!append_envp_entry(shell, "OLDPWD", ""))
		return (0);
	if (!append_envp_entry(shell, "SHLVL", "1"))
		return (0);
	return (1);
}

static int	init_custom_envp(t_shell *shell)
{
	char	*cwd;
	int		ok;

	shell->envp = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	ok = append_custom_envp(shell, cwd);
	free(cwd);
	if (!ok)
		free_envp_list(&shell->envp);
	return (ok);
}

static void	fill_envp_from_tab(t_shell *shell, char **envp)
{
	char	*key;
	char	*value;
	t_envp	*new_node;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		if (parse_env_var(envp[i], &key, &value))
		{
			new_node = create_envp_node(key, value);
			if (new_node)
				envp_add_back(&shell->envp, new_node);
			free(key);
			free(value);
		}
		i++;
	}
}

void	init_envp(t_shell *shell, char **envp)
{
	shell->envp = NULL;
	if (!envp || !*envp || !**envp)
	{
		init_custom_envp(shell);
		return ;
	}
	fill_envp_from_tab(shell, envp);
}
