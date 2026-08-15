/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/29 18:06:37 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

size_t	ft_fprintf_putchar_fd_pf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_fprintf_putstr_fd_pf(const char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		return (ft_fprintf_putstr_fd_pf("(null)", fd));
	}
	while (s[i])
	{
		ft_fprintf_putchar_fd_pf(s[i], fd);
		i++;
	}
	return (i);
}
