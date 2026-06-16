/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:55:40 by lucinguy          #+#    #+#             */
/*   Updated: 2026/06/16 18:21:01 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// Signals for interactive mode
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_readline_state & RL_STATE_READCMD)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
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

int	setup_signal_heredoc(void)
{
	struct sigaction	sa;
	int sig = 0;
	sa.sa_handler = sig_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sig = sigaction(SIGINT, &sa, NULL);
	sig = sigaction(SIGQUIT, &sa, NULL);
	return sig;
}

void	sig_heredoc(int sig)
{
	(void)sig;
}