/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:45:38 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/27 13:02:45 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putchar_fd_pf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_putstr_fd_pf(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		return (ft_putstr_fd_pf("(null)", fd));
	}
	while (s[i])
	{
		ft_putchar_fd_pf(s[i], fd);
		i++;
	}
	return (i);
}
