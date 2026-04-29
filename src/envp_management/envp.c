/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:42:56 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/30 01:20:51 by lucinguy         ###   ########.fr       */
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

// CHANGER CWD/ALLOCATION ET AJOUTER GET HOME FUNCTION !!!
void	custom_envp(t_shell *shell)
{
	char	*cwd;

	shell->envp = malloc(5 * sizeof(char *));
	if (!shell->envp)
		return (perror("Custom envp initialisation failed."));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(shell->envp),
			perror("Custom envp initialisation failed."));
	shell->envp[0] = ft_strdup("HOME=");
	if (!shell->envp[0])
		return (free(cwd), free_custom_envp(shell->envp, 0),
			perror("Custom envp initialisation failed."));
	shell->envp[1] = ft_strdup("PATH=/usr/lib64/ccache:/usr/local/bin:/usr/bin");
	if (!shell->envp[1])
		return (free(cwd), free_custom_envp(shell->envp, 1),
			perror("Custom envp initialisation failed."));
	shell->envp[2] = ft_strjoin("PWD=", cwd);
	if (!shell->envp[2])
		return (free(cwd), free_custom_envp(shell->envp, 2),
			perror("Custom envp initialisation failed."));
	shell->envp[3] = ft_strjoin("OLDPWD=", cwd);
	if (!shell->envp[3])
		return (free(cwd), free_custom_envp(shell->envp, 3),
			perror("Custom envp initialisation failed."));
	shell->envp[4] = NULL;
	free(cwd);
}
