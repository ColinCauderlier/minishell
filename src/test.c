/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/24 12:14:43 by ccauderl         ###   ########.fr       */
=======
/*   Updated: 2026/04/24 15:09:11 by lucinguy         ###   ########.fr       */
>>>>>>> aeb1928e3e868750c19b7e7ce9a3d8138436dddf
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"
#include "../includes/includes.h"

<<<<<<< HEAD
void	sig_handler(int sig)
{
	write(1, "Minishell>^C\n", 13);
	sig++;
	sig--;
}

char	*get_prompt()
{
	char	*prompt;

	prompt = readline("Minishell>");
	return (prompt); 
}

int	main()
=======
int	main(void)
>>>>>>> aeb1928e3e868750c19b7e7ce9a3d8138436dddf
{
	char	*prompt;

	signal(SIGINT, sig_handler);
	prompt = "";
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = get_prompt();
		tokenize(prompt);
	}
	return (0);
}
