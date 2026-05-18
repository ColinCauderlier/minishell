/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:58:25 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/18 20:08:11 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	a;
	unsigned char	b;

	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	a = (unsigned char)*s1;
	b = (unsigned char)*s2;
	return ((int)a - (int)b);
}
