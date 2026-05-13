/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:42:56 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/13 14:00:35 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	init_custom_envp(t_shell *shell)
{
	char	cwd[4096];

	shell->envp[6][4104] = '\0';
	if (getcwd(cwd, 4096) == NULL)
		return (0);
	shell->envp[0] = ft_strdup("HOME=");
	shell->envp[1] = ft_strjoin("OLDPWD=", cwd);
	shell->envp[2] = ft_strdup("PATH=/usr/lib64/ccache:/usr/local/bin:/usr/bin");
	shell->envp[3] = ft_strjoin("PWD=", cwd);
	shell->envp[4] = ft_strdup("SHLVL=1");
	shell->envp[5] = NULL;
	return (1);
}

void init_envp(t_shell *shell, char **env)
{
	if (!env)
	{
		shell->custom_envp = 1;
		init_custom_envp(shell);
	}
	else
	{
		shell->custom_envp = 0;
		shell->envp = env;
	}
}
