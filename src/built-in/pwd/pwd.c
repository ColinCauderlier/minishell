/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:15:11 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/28 19:46:06 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

// get the path, store it in buffer, size of buffer is 4096 (max path length on linux)
// if buffer is NULL (= error), enter the condition and error is stocked in errno
// depending on the error message in errno, display different error message

int	pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == NULL)
	{
		ft_putstr_fd("bash: pwd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}
