/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:13:27 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/26 14:47:47 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	int				*string;
	unsigned int	i;
	unsigned int	nb;

	nb = 10;
	i = 0;
	string = ft_calloc(nb, sizeof(int));
	if (!string)
	{
		printf("Oups, y'a un souci !");
		return (1);
	}
	while (i < 10)
	{
		printf("%d ", string[i]);
		i++;
	}
	free(string);
}
*/