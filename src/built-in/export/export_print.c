/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/21 22:26:32 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	print_export_value(char *value)
{
	int	i;

	i = 0;
	while (value && value[i])
	{
		if (value[i] == '"' || value[i] == '\\')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(value[i], STDOUT_FILENO);
		i++;
	}
}

void	print_export_env(t_shell *shell)
{
	int		index;
	char	*equal;

	if (!shell || !shell->exp)
		return ;
	ft_sort_strings(envp_size(shell->exp), shell->exp);
	index = 0;
	while (shell->exp[index])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equal = ft_strchr(shell->exp[index], '=');
		if (!equal)
			ft_putstr_fd(shell->exp[index], STDOUT_FILENO);
		else
		{
			write(STDOUT_FILENO, shell->exp[index], equal - shell->exp[index]);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			print_export_value(equal + 1);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		index++;
	}
}
