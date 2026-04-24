/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/24 15:09:11 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/functions.h"
#include "../includes/includes.h"

int	main(void)
{
	char	*prompt;

	prompt = "";
	while (ft_strncmp(prompt, "exit", 4) != 0)
	{
		prompt = readline("Minishell>");
		tokenize(prompt);
	}
	return (0);
}
