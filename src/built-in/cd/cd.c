/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:29:15 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/13 14:25:15 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// send path to chdir function

int	cd(char *path, t_shell *shell)
{
	(void)shell;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	else
	{
		update_envp(shell, "PWD", getcwd);
		return (0);
	}
}

