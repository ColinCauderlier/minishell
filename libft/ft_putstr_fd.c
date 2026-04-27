/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:17:08 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/27 15:02:44 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	int	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	return (len);
// }

void	ft_putstr_fd(char const *s, int fd)
{
	int		i;
	size_t	len;

	i = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

// int	main(void)
// {
// 	ft_putstr_fd("oui\n", 1);
// }
