/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:20:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/21 22:27:06 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	export_is_valid_identifier(char *arg)
{
	int	i;

	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export_find_index(char **array, char *name)
{
	int	len;
	int	i;

	if (!array || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], name, len) == 0 && (array[i][len] == '='
			|| array[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	envp_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	*export_get_name(char *arg)
{
	size_t	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

char	*export_get_value(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (ft_strdup(""));
	return (ft_strdup(equal + 1));
}
