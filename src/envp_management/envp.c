/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:42:56 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/18 15:25:25 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	free_env_copy(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static char	*get_next_shlvl(char **env)
{
	int		i;
	int		level;
	char	*value;

	i = 0;
	level = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			level = ft_atoi(env[i] + 6);
			break ;
		}
		i++;
	}
	value = ft_itoa(level + 1);
	return (value);
}

static char	**duplicate_env(char **env)
{
	int		i;
	char	**new;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	new = ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (free_env_copy(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

static int	init_custom_envp(t_shell *shell)
{
	char	cwd[4096];

	shell->envp = ft_calloc(6, sizeof(char *));
	if (!shell->envp)
		return (0);
	if (getcwd(cwd, 4096) == NULL)
		return (free_env_copy(shell->envp), shell->envp = NULL, 0);
	shell->envp[0] = ft_strdup("HOME=");
	shell->envp[1] = ft_strjoin("OLDPWD=", cwd);
	shell->envp[2] = ft_strdup("PATH=/usr/lib64/ccache:/usr/local/bin:"
								"/usr/bin");
	shell->envp[3] = ft_strjoin("PWD=", cwd);
	shell->envp[4] = ft_strdup("SHLVL=1");
	shell->envp[5] = NULL;
	if (!shell->envp[0] || !shell->envp[1] || !shell->envp[2] || !shell->envp[3]
		|| !shell->envp[4])
		return (free_env_copy(shell->envp), shell->envp = NULL, 0);
	return (1);
}

void	init_envp(t_shell *shell, char **env)
{
	char	*shlvl;

	if (!env || !env[0])
	{
		shell->custom_envp = 1;
		if (!init_custom_envp(shell))
			return ;
	}
	else
	{
		shell->envp = duplicate_env(env);
		if (!shell->envp)
			return (shell->custom_envp = 1, (void)init_custom_envp(shell));
		shell->custom_envp = 1;
		shlvl = get_next_shlvl(shell->envp);
		if (shlvl)
		{
			update_envp(shell, "SHLVL", shlvl);
			free(shlvl);
		}
	}
}
