/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:29:15 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/27 16:00:53 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	cd(char *path)
{
	if (chdir(path) == -1) //send path to chdir function -> change cwd to the one specified in path
	{
		perror("Cannot change current directory.\n");
		if (errno == EACCES)
			perror("Permission denied.\n");
		if (errno == EFAULT)
			perror("Directory not accessible.\n");
		if (errno == EIO)
			perror("An I/O has occurred.\n");
		if (errno == ELOOP)
			perror("Too many symbolic links encountered.\n");
		if (errno == ENAMETOOLONG)
			perror("Path too long.\n");
		if (errno == ENOENT)
			perror("Directory does not exist.\n");
		if (errno == ENOMEM)
			perror("Insufficient kernel memory available.\n");
		if (errno == ENOTDIR)
			perror("Not a directory.\n");
	}
}
