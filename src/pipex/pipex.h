/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:51:42 by ccauderl          #+#    #+#             */
/*   Updated: 2026/02/23 17:18:33 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

//-------LIBRARIES-------//

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

//-------STRUCTURES-------//

typedef struct s_process_arguments {
	char	*files[2];
	char	**envp;
	char	***commands;
	int		**pipes;
	int		*pids;
}	t_proc_args;

//-------FUNCTIONS-------//

void	close_fd(int fd[2]);
void	execute_command(t_proc_args *args, int i);
char	***init_commands(char **argv, int argc);
void	init_args(t_proc_args *args, char **envp, char **argv, int argc);
void	free_split(char **strs);
void	free_commands(char ***commands);
char	*find_path(char *command, char **envp);
void	check_nb_arguments(int argc);
void	error(t_proc_args *args, int index_file, char **command);
void	close_all_pipes(t_proc_args *args);
void	free_all_pipes(t_proc_args *args);
void	first_cmd(t_proc_args *args);
void	middle_cmd(t_proc_args *args, int i);
void	last_cmd(t_proc_args *args, int i);

#endif
