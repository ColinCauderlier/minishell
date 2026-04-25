/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:15:11 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/25 23:43:18 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == NULL) //get the path, store it in buffer, size of buffer is 4096 (max path length on linux) / if buffer is NULL (= error), enter the condition and error is stocked in errno
	{
		ft_putstr_fd("Cannot get current working directory path\n", 2);
		if (errno == ERANGE) //depending on the error message in errno, display different error message
			ft_putstr_fd("Buffer size is too small.\n", 2);
		else if (errno == EACCES)
			ft_putstr_fd("You don't have permissions to access directory.\n",
				2);
		else if (errno == EFAULT)
			ft_putstr_fd("Buffer pointer is invalid.\n", 2);
		else if (errno == EINVAL)
			ft_putstr_fd("Buffer size is invalid.\n", 2);
		else if (errno == EIO)
			ft_putstr_fd("Input/output error has occured\n", 2);
		exit(EXIT_FAILURE);
	}
	else
		ft_printf("%s\n", buffer); //print buffer content (= path)
}
