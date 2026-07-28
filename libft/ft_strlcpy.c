/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 01:57:46 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/11 12:51:06 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (dsize == 0)
		return (len);
	i = 0;
	while (src[i] && i + 1 < dsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}