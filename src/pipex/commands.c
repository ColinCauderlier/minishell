/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:20:36 by ccauderl          #+#    #+#             */
/*   Updated: 2026/02/22 18:56:47 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_proc_args *args)
{
	int	fd_infile;

	fd_infile = open(args->files[0], O_RDONLY);
	if (fd_infile == -1)
	{
		error(args, 0, NULL);
		free_all_pipes(args);
		free_commands(args->commands);
		exit(1);
	}
	dup2(fd_infile, STDIN_FILENO);
	dup2(args->pipes[0][1], STDOUT_FILENO);
	close_all_pipes(args);
	close(fd_infile);
	execute_command(args, 0);
}

void	last_cmd(t_proc_args *args, int i)
{
	int	fd_outfile;

	fd_outfile = open(args->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
	{
		error(args, 1, NULL);
		free_all_pipes(args);
		free_commands(args->commands);
		exit(1);
	}
	dup2(fd_outfile, STDOUT_FILENO);
	dup2(args->pipes[i - 1][0], STDIN_FILENO);
	close(fd_outfile);
	close_all_pipes(args);
	execute_command(args, i);
}

void	middle_cmd(t_proc_args *args, int i)
{
	dup2(args->pipes[i][1], STDOUT_FILENO);
	dup2(args->pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(args);
	execute_command(args, i);
}
