/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:08:12 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/21 22:24:27 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	append_export_argument(char *arg, t_shell *shell)
{
	char	*name;
	char	*value;

	name = export_get_name(arg);
	if (!name)
		return (1);
	if (!ft_strchr(arg, '='))
	{
		if (!update_named_array(&shell->exp, name, NULL))
			return (free(name), 1);
		free(name);
		return (0);
	}
	value = export_get_value(arg);
	if (!value)
		return (free(name), 1);
	update_envp(shell, name, value);
	free(name);
	free(value);
	return (0);
}

int	export(char **command, t_shell *shell)
{
	int	i;
	int	status;

	if (!command || !command[0])
		return (0);
	if (!command[1])
	{
		print_export_env(shell);
		return (0);
	}
	i = 1;
	status = 0;
	while (command[i])
	{
		if (!export_is_valid_identifier(command[i]))
		{
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				command[i]);
			status = 1;
		}
		else if (append_export_argument(command[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}
