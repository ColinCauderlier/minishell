/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 05:10:08 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 15:57:30 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*find;

	find = NULL;
	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			find = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (find);
}