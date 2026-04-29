/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/29 13:29:28 by ccauderl         ###   ########.fr       */
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

	(void)argv;
	if (argc != 1)
		return (1);
	signal(SIGINT, sig_handler);
	prompt = "";
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = get_prompt();
		if (ft_strncmp(prompt, "pwd", 3) == 0)
			pwd();
		tokenize(prompt, envp);
	}
	return (0);
}

// int main(void) //test cd
// {
// 	cd("home/lucinguy/cercle3");
// 	return (0);
// }
