/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/18 16:28:07 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

/*
void	sig_handler(int sig)
{
	(void)sig;
	write(1, "Minishell>^C\n", 13);
	sig++;
	sig--;
}
*/

void	free_envp(t_shell *shell)
{
	int		i;

	if (shell->custom_envp && shell->envp)
	{
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_shell	shell;
	int		status;

	(void)argv;
	(void)argc;
	//	signal(SIGINT, sig_handler);
	init_envp(&shell, envp);
	prompt = "";
	shell.last_exit = 0;
	status = 0;
	if (tcgetattr(STDIN_FILENO, &(shell.term_ctl)) == -1)
	{
		perror("minishell: ");
		return (errno);
	}
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(shell.term_ctl));
		prompt = readline("Minishell > ");
		if (!prompt)
			break ;
		add_history(prompt);
		if (ft_strncmp(prompt, ":", 2) == 0)
		{
			free(prompt);
			continue ;
		}
		if (ft_strncmp(prompt, "exit", 5) == 0)
		{
			free(prompt);
			break ;
		}
		status = tokenize(prompt, &shell);
		if (status == 1)
			return (free_all_tokens(&shell), 1);
		else if (status != 2)
			exec(&shell);
		free_all_tokens(&shell);
		free(prompt);
	}
	free_envp(&shell);
	return (0);
}
