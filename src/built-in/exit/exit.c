/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:40:40 by lucinguy          #+#    #+#             */
/*   Updated: 2026/06/01 18:55:06 by lucinguy         ###   ########.fr       */
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
	return ((int)(result * sign));
}

int	exit_code(char **cmd)
{
	int	error;
	int	num_len;
	int	i;

	error = 0;
	i = 0;
	num_len = ft_strlen(cmd[1]);
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			perror("Given argument is not an int.");
			return (-1);
		}
		i++;
	}
	error = ft_atol(cmd[1]);
	return (error);
}

int	ft_exit(char **cmd)
{
	if (!cmd[1])
		ft_printf("exit\n");
}
