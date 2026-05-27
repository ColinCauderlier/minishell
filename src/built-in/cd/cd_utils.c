/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:29:15 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/27 18:20:02 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

char	*get_env_value(t_shell *shell, char *name)
{
	int	i;
	int	len;

	if (!shell || !shell->envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, len) == 0
			&& shell->envp[i][len] == '=')
			return (shell->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_target_path(char *path, t_shell *shell, int *print_path)
{
	char	*home_or_old;

	if (print_path)
		*print_path = 0;
	if (!path)
		path = "~";
	if (ft_strcmp(path, "-") == 0)
	{
		home_or_old = get_env_value(shell, "OLDPWD");
		if (!home_or_old)
			return (NULL);
		if (print_path)
			*print_path = 1;
		return (ft_strdup(home_or_old));
	}
	if (ft_strcmp(path, "~") == 0 || (path[0] == '~' && path[1] == '/'))
	{
		home_or_old = get_env_value(shell, "HOME");
		if (!home_or_old)
			return (NULL);
		if (ft_strcmp(path, "~") == 0)
			return (ft_strdup(home_or_old));
		return (ft_strjoin(home_or_old, path + 1));
	}
	return (ft_strdup(path));
}

void	print_cd_error(char *path)
{
	if (!path || ft_strcmp(path, "~") == 0 || (path[0] == '~'
			&& path[1] == '/'))
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (ft_strcmp(path, "-") == 0)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}

int	perform_cd_update(t_shell *shell, char *target, int print_path)
{
	char	temp[4096];

	if (getcwd(temp, 4096) == NULL)
	{
		perror("Could not retrieve current working directory.");
		return (1);
	}
	if (chdir(target) != 0)
	{
		print_cd_error(target);
		return (1);
	}
	update_envp(shell, "OLDPWD", temp);
	if (getcwd(temp, 4096) == NULL)
		return (1);
	update_envp(shell, "PWD", temp);
	if (print_path)
		ft_putendl_fd(target, STDOUT_FILENO);
	return (0);
}
