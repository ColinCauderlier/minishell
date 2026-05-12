/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:15:11 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/12 19:11:23 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// Print current working directory into a 4096-byte buffer; on error
// print strerror(errno) to stderr
// print buffer content (= path)

int	pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == NULL)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	else
		ft_printf("%s\n", buffer);
	return (0);
}
