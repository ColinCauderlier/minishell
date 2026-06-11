/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:40:40 by lucinguy          #+#    #+#             */
/*   Updated: 2026/06/11 19:53:17 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	size_t	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	is_numeric_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	cleanup_before_exit(t_shell *shell)
{
	free_exec(shell);
	free_envp(shell);
	free_all_tokens(shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	ft_exit(char **cmd, t_shell *shell)
{
	int	status;

	if (cmd[1] && cmd[2])
		return (ft_fprintf(2, "minishell: exit: too many arguments\n"), 1);
	if (!cmd[1])
		status = shell->last_exit;
	else
	{
		if (!is_numeric_arg(cmd[1]))
		{
			ft_fprintf(2, "minishell: exit: %s: numeric argument required\n",
				cmd[1]);
			status = 2;
		}
		else
			status = (unsigned char)ft_atol(cmd[1]);
	}
	cleanup_before_exit(shell);
	exit(status);
	return (status);
}
