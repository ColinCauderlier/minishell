/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:55:40 by lucinguy          #+#    #+#             */
/*   Updated: 2026/06/18 20:02:56 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// Set up signals for interactive mode
int	setup_signal_inter(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	g_signal = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1 || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
		return (perror("minishell: signal"), 1);
	return (0);
}

// Signals for interactive mode
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// Signals for child processes
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Behaviour for EOF/'prompt == NULL'
void	set_exit_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_fprintf(2, "Quit (core dumped)\n");
		shell->last_exit = 128 + WTERMSIG(status);
	}
	else
		shell->last_exit = status;
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	g_signal = sig;
}
