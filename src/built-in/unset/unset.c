/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:00:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/29 17:05:17 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	unset_one(char *arg, t_shell *shell)
{
	char	*name;
	int		status;

	if (!export_is_valid_identifier(arg))
	{
		ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n", arg);
		return (1);
	}
	name = export_get_name(arg);
	if (!name)
		return (1);
	status = 0;
	if (!remove_named_array(&shell->envp, name))
		status = 1;
	if (shell->exp && !remove_named_array(&shell->exp, name))
		status = 1;
	free(name);
	return (status);
}

int	unset(char **command, t_shell *shell)
{
	int	i;
	int	status;

	if (!command || !command[0])
		return (0);
	i = 1;
	status = 0;
	while (command[i])
	{
		if (unset_one(command[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}
