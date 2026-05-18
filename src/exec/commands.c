/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:20:36 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/16 15:42:25 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	first_cmd(t_shell *shell)
{
	dup2(shell->exec.pipes[0][1], STDOUT_FILENO);
	close_all_pipes(shell);
	execute_command(shell, 0);
}

void	last_cmd(t_shell *shell, int i)
{
	dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(shell);
	execute_command(shell, i);
}

void	middle_cmd(t_shell *shell, int i)
{
	dup2(shell->exec.pipes[i][1], STDOUT_FILENO);
	dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(shell);
	execute_command(shell, i);
}
/*
void	first_cmd(t_shell *shell)
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
	dup2(shell->exec.pipes[0][1], STDOUT_FILENO);
	close_all_pipes(shell);
	close(fd_infile);
	execute_command(shell, 0);
}

void	last_cmd(t_shell *shell, int i)
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
	dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	close(fd_outfile);
	close_all_pipes(shell);
	execute_command(shell, i);
}

void	middle_cmd(t_shell *shell, int i)
{
	dup2(shell->exec.pipes[i][1], STDOUT_FILENO);
	dup2(shell->exec.pipes[i - 1][0], STDIN_FILENO);
	close_all_pipes(shell);
	execute_command(shell, i);
}*/
