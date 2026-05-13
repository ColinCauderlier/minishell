/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:08:12 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/13 14:26:31 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"


//Regarde si la variable existe : si oui, la met a jour, sinon, en cree une nouvelle a la suite

void	update_envp(t_shell *shell, char *var_name, char *var_value)
{
	int		i;
	int		j;
	char	*var;
	int		len;

	i = 0;
	j = 0;
	var = ft_strjoin(var_name, "=");
	len = ft_strlen(var_name);
	while (shell->envp[i])
	{
		if (strncmp(var, shell->envp[i], len) == 0)
		{
			shell->envp[i] = ft_strjoin(var, var_value);
			return;
		}
		i++;
	}
	shell->envp[i++] = ft_strjoin(var, var_value);
	return;
}
