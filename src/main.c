/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/07 15:45:06 by ccauderl         ###   ########.fr       */
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
char	*get_prompt(void)
{
	char	*prompt;

	prompt = readline("Minishell >");
	return (prompt);
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
	while (ft_strncmp(prompt, "exit\0", 5) != 0)
	{
		prompt = get_prompt();
		status = tokenize(prompt, &shell);
		if (status == 1)
			return (free_all_tokens(&shell), 1);
		else if (status != 2)
			exec(&shell);
	}
	free(prompt);
	free_all_tokens(&shell);
	return (0);
}
