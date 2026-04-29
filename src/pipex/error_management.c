/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:37:56 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 17:39:11 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_nb_arguments(int argc)
{
	if (argc >= 5)
		return ;
	ft_fprintf(2, "ERROR_NB_ARG: Too few arguments\n");
	ft_fprintf(2, "The program should be executed as follows :\n");
	ft_fprintf(2, "./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	exit(1);
}

void	free_all_pipes(t_proc_args *args)
{
	int	i;

	i = 0;
	while (args->pipes[i])
	{
		free(args->pipes[i]);
		i++;
	}
	free(args->pipes);
}

void	close_all_pipes(t_proc_args *args)
{
	int	i;

	i = 0;
	while (args->pipes[i])
	{
		close_fd(args->pipes[i]);
		i++;
	}
}

void	error(t_proc_args *args, int index_file, char **command)
{
	int	temp_errno;
	int	i;

	temp_errno = errno;
	i = 0;
	if (temp_errno)
		ft_fprintf(2, "pipex: %s", strerror(errno));
	else
		ft_fprintf(2, "pipex: command not found");
	if (index_file == 0 || index_file == 1)
		ft_fprintf(2, ": %s", args->files[index_file]);
	if (command)
	{
		ft_fprintf(2, ": ");
		while (command[i])
		{
			ft_fprintf(2, "%s ", command[i]);
			i++;
		}
	}
	ft_fprintf(2, "\n");
	close_all_pipes(args);
	errno = temp_errno;
}
