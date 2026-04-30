/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/30 20:10:03 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	sig_handler(int sig)
{
	(void)sig;
	write(1, "Minishell>^C\n", 13);
	sig++;
	sig--;
}

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

	(void)argv;
	if (argc != 1)
		return (1);
	signal(SIGINT, sig_handler);
	prompt = "";
	shell.envp = envp;
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = get_prompt();
		if (tokenize(prompt, &shell) == 1)
			return (free_all_tokens(&shell), 1);
		if (ft_strncmp(prompt, "pwd", 3) == 0)
			pwd();
	}
	free_all_tokens(&shell);
	return (0);
}

// int main(void) //test cd
// {
// 	cd("/home/Oswen/42/Devoirs/");
// 	return (0);
// }
