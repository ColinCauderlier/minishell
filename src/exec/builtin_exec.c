/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:04:03 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/19 12:19:38 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//If the command is a builtin, return its id, return 0 otherwise
int	check_builtin(char **command)
{
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (2);
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (3);
	return (0);
}

int	exec_builtin(t_shell *shell, char **command, int id)
{
	int	len_command;

	len_command = 0;
	while (command[len_command])
		len_command++;
	if (id == 1)
	{
		if (len_command > 2)
		{
			ft_fprintf(2, "minishell: cd: too many arguments\n");
			return (1);
		}
		else
			return (cd(command[1], shell));
	}
	if (id == 2)
		return (pwd());
	if (id == 3)
		return (env(shell));
	return (0);
}
