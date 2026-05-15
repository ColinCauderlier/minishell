/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 23:46:49 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/14 17:28:31 by ccauderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return (free(s1), free(s2), NULL);
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (free(s1), free(s2), res);
}

/*
#include <stdio.h>

int	main(void)
{
	char	s1[] = "hello ";
	char	s2[] = "world\n";
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	printf("%s", s3);
	free(s3);
}
*/
