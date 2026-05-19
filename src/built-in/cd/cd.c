/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:29:15 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/19 12:55:50 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// send path to chdir function

int	cd(char *path, t_shell *shell)
{
	char	temp[4096];

	if (getcwd(temp, 4096) == NULL)
	{
		perror("Could not retrieve current working directory.");
		return (1);
	}
	if (chdir(path) == 0)
	{
		update_envp(shell, "OLDPWD", temp);
		getcwd(temp, 4096);
		update_envp(shell, "PWD", temp);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
}
