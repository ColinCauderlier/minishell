/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:24:53 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/26 19:32:03 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static int	valid_option(char *command)
{
	int	i;

	i = 1;
	if (ft_strncmp(command, "-n", 3) == 0)
		return (0);
	else if (command[0] == '-' && command[1] != '\0')
	{
		while (command[i])
		{
			if (command[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
	return (0);
}

static void	print_strings(char **command)
{
	int	i;
	int	size;
	int	trail;

	i = 1;
	trail = 1;
	size = envp_size(command);
	while (command[i])
	{
		if (valid_option(command[i]) == 0 && i < size)
		{
			trail = 0;
			i++;
			continue ;
		}
		ft_putstr_fd(command[i], STDOUT_FILENO);
		if (i == size && valid_option(command[size]) == 0)
			break ;
		i++;
		if (i < size && i != 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (trail == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

int	echo(char **command)
{
	int	i;

	i = 1;
	if (!command[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	print_strings(command);
	return (0);
}
