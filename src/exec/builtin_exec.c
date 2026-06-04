/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:04:03 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/04 17:12:25 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//If the command is a builtin, return its id, return 0 otherwise
int     check_builtin(char **command)
{
	if (!command || !command[0])
		return (0);
        if (ft_strncmp(command[0], "cd", 3) == 0)
                return (1);
        if (ft_strncmp(command[0], "pwd", 4) == 0)
                return (2);
        if (ft_strncmp(command[0], "env", 4) == 0)
                return (3);
        if (ft_strncmp(command[0], "export", 7) == 0)
                return (4);
        if (ft_strncmp(command[0], "echo", 5) == 0)
                return (5);
        return (0);
}

int     exec_builtin(t_shell *shell, char **command, int id)
{
        int     len_command;

        len_command = 0;
        while (command[len_command])
                len_command++;
        if (id == 1)
        {
                if (len_command > 2)
                        return (ft_fprintf(2, "minishell: cd: too many arguments\n"), 1);
                return (cd(command[1], shell));
        }
        if (id == 2)
                return (pwd());
        if (id == 3)
        {
                if (len_command >= 2)
                        return (ft_fprintf(2, "minishell: env: too many arguments\n"), 1);
                return (env(shell));
        }
        if (id == 4)
                return (export(command, shell));
        if (id == 5)
                return (echo(command));
        return (0);
}

