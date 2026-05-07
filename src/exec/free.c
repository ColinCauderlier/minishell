/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccauderl <ccauderl@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 17:06:16 by ccauderl          #+#    #+#             */
/*   Updated: 2026/05/06 17:07:53 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free_split(commands[i]);
		i++;
	}
	free(commands);
}
