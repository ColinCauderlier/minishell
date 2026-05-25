/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 19:24:53 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/25 19:56:00 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	echo(char **commands)
{
	int	i;
	int	trail;

	i = 1;
	trail = 1;
	if (!commands[i])
	{
		if (trail == 1)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (ft_strncmp(commands[1], "-n", 3) == 0)
	{
		trail = 0;
		i = 2;
	}
	while (commands[i])
	{
		ft_putstr_fd(commands[i], STDOUT_FILENO);
		i++;
	}
	if (trail == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
