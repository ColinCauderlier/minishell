/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 14:52:31 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/29 17:09:48 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

char	*get_home(char *pwd)
{
	int		slash;
	int		i;
	char	*home;
	int		len;

	slash = 0;
	i = 0;
	len = 0;
	while (pwd[len] && len < 4096)
	{
		if (pwd[len + 1] == '/' && slash == 2)
			break ;
		if (pwd[len] == '/')
			slash++;
		len++;
	}
	home = malloc(len * sizeof(char) + 1);
	if (!home)
		return (NULL);
	while (i < len)
	{
		home[i] = pwd[i];
		i++;
	}
	home[i] = '\0';
	return (home);
}