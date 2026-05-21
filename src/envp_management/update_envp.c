/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/21 22:25:47 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	*build_entry(char *var_name, char *var_value)
{
	char	*prefix;
	char	*entry;

	if (!var_value)
		return (ft_strdup(var_name));
	prefix = ft_strjoin(var_name, "=");
	if (!prefix)
		return (NULL);
	entry = ft_strjoin(prefix, var_value);
	free(prefix);
	return (entry);
}

static int	extend_array(char ***array, char *new_var)
{
	char	**new_array;
	int		i;
	int		size;

	if (!array)
		return (0);
	size = envp_size(*array);
	new_array = ft_calloc(size + 2, sizeof(char *));
	if (!new_array)
		return (0);
	i = 0;
	while (i < size)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[i] = new_var;
	new_array[i + 1] = NULL;
	free(*array);
	*array = new_array;
	ft_sort_strings(size + 1, *array);
	return (1);
}

int	update_named_array(char ***array, char *var_name, char *var_value)
{
	char	*new_var;
	int		index;

	if (!array)
		return (0);
	index = export_find_index(*array, var_name);
	if (!var_value && index != -1)
		return (1);
	new_var = build_entry(var_name, var_value);
	if (!new_var)
		return (0);
	if (index != -1)
	{
		free((*array)[index]);
		(*array)[index] = new_var;
		ft_sort_strings(envp_size(*array), *array);
		return (1);
	}
	if (!extend_array(array, new_var))
		return (free(new_var), 0);
	return (1);
}

void	update_envp(t_shell *shell, char *var_name, char *var_value)
{
	if (!shell)
		return ;
	if (!update_named_array(&shell->envp, var_name, var_value))
		return ;
	update_named_array(&shell->exp, var_name, var_value);
}
