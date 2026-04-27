/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:15:11 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/27 15:54:04 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, 4096) == NULL) //get the path, store it in buffer, size of buffer is 4096 (max path length on linux) / if buffer is NULL (= error), enter the condition and error is stocked in errno
	{
		perror("Cannot get current working directory path\n");
		if (errno == ERANGE) //depending on the error message in errno, display different error message
			perror("Buffer size is too small.\n");
		else if (errno == EACCES)
			perror("You don't have permissions to access directory.\n");
		else if (errno == EFAULT)
			perror("Buffer pointer is invalid.\n");
		else if (errno == EINVAL)
			perror("Buffer size is invalid.\n");
		else if (errno == EIO)
			perror("Input/output error has occured\n");
		exit(EXIT_FAILURE);
	}
	else
		ft_printf("%s\n", buffer); //print buffer content (= path)
}

