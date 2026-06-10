/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/06/10 17:13:36 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	free_env_copy(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_envp(t_shell *shell)
{
	if (shell->envp)
	{
		free_env_copy(shell->envp);
		shell->envp = NULL;
	}
	if (shell->exp)
	{
		free_env_copy(shell->exp);
		shell->exp = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char				*prompt;
	t_shell				shell;
	int					status;
	struct sigaction	sa;

	(void)argv;
	(void)argc;
	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1 || signal(SIGQUIT,
			SIG_IGN) == SIG_ERR)
		return (perror("minishell: signal"), 1);
	shell = (t_shell){0};
	init_envp(&shell, envp);
	prompt = "";
	shell.last_exit = 0;
	status = 0;
	if (tcgetattr(STDIN_FILENO, &(shell.term_ctl)) == -1)
		return (perror("minishell: "), errno);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(shell.term_ctl));
		prompt = readline("Minishell > ");
		if (!prompt)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		add_history(prompt);
		status = tokenize(prompt, &shell);
		if (status == 1)
			return (free(prompt), free_all_tokens(&shell), free_envp(&shell),
				1);
		else if (status != 2)
			exec(&shell);
		free_all_tokens(&shell);
		free(prompt);
	}
	free_envp(&shell);
	return (0);
}
