/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:08:12 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/18 20:44:11 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static int	envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

static int	extend_envp(t_shell *shell, char *new_var)
{
	char	**new_envp;
	int		i;
	int		size;

	size = envp_size(shell->envp);
	new_envp = ft_calloc(size + 2, sizeof(char *));
	if (!new_envp)
		return (0);
	i = 0;
	while (i < size)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	ft_sort_strings(size + 1, shell->envp);
	return (1);
}

static int	update_existing(t_shell *shell, char *var, char *var_value, int len)
{
	int		i;
	char	*new;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(var, shell->envp[i], len) == 0)
		{
			new = ft_strjoin(var, var_value);
			if (!new)
				return (-1);
			free(shell->envp[i]);
			shell->envp[i] = new;
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_envp(t_shell *shell, char *var_name, char *var_value)
{
	char	*var;
	int		len;
	char	*new;
	int		status;

	var = ft_strjoin(var_name, "=");
	if (!var)
		return ;
	len = ft_strlen(var);
	status = update_existing(shell, var, var_value, len);
	if (status != 0)
		return (free(var));
	new = ft_strjoin(var, var_value);
	if (!new)
		return (free(var));
	if (!extend_envp(shell, new))
		free(new);
	free(var);
}
