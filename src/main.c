/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/27 16:01:09 by lucinguy         ###   ########.fr       */
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

int	main(void)
{
	char	*prompt;

	signal(SIGINT, sig_handler);
	prompt = "";
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = get_prompt();
		if (ft_strncmp(prompt, "pwd", 3) == 0)
			pwd();
		tokenize(prompt);
	}
	return (0);
}

// int main(void) //test cd
// {
// 	cd("home/lucinguy/cercle3");
// 	return (0);
// }
