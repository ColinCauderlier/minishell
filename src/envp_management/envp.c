/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:42:56 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/15 16:45:12 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	free_custom_envp(char **envp, size_t count)
{
	while (count > 0)
	{
		count--;
		free(envp[count]);
	}
	free(envp);
}

static int	init_custom_envp(t_shell *shell)
{
	char	cwd[4096];

	shell->envp = malloc(5 * sizeof(char *));
	if (!shell->envp[0])
		return (0);
	shell->envp = NULL;
	if (getcwd(cwd, 4096) == NULL)
		return (free_custom_envp(shell->envp, 4), 0);
	shell->envp[0] = ft_strdup("HOME=");
	shell->envp[1] = ft_strdup("PATH=/usr/lib64/ccache:/usr/local/bin:/usr/bin");
	shell->envp[2] = ft_strjoin("PWD=", cwd);
	shell->envp[3] = ft_strjoin("OLDPWD=", cwd);
	shell->envp[4] = NULL;
	return (1);
}

void init_envp(t_shell *shell, char **env)
{
	if (!env)
		init_custom_envp(shell);
	else
		shell->envp = env;
}
