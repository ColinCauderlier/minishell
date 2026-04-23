/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:36:08 by ccauderl          #+#    #+#             */
/*   Updated: 2026/04/20 18:06:39 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external_include.h"

int	main()
{
	char	*prompt;
	
	prompt = readline("Minishell>");
	printf("%s\n", prompt);
	return (0);
}
