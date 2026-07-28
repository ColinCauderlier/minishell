/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 01:36:18 by lucinguy          #+#    #+#             */
/*   Updated: 2026/05/29 17:17:23 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Trims [set] chars at start and end of [s1]

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	while (len--)
		out[len] = s1[start + len];
	out[end - start] = '\0';
	return (out);
}