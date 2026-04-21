/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:27:02 by lucinguy          #+#    #+#             */
/*   Updated: 2026/03/03 14:10:51 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_t_fd(long n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += ft_putchar_fd_pf('-', fd);
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_t_fd(n / 10, fd);
	ft_putchar_fd_pf(n % 10 + 48, fd);
	return (count + 1);
}

int	ft_putnbr_base_x(unsigned long n, int uppercase, int fd)
{
	char	*base;
	int		count;

	count = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		count += ft_putnbr_base_x(n / 16, uppercase, fd);
	write(fd, &base[n % 16], 1);
	return (count + 1);
}

int	ft_putpointer(unsigned long n, int fd)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		ft_putstr_fd_pf("(nil)", fd);
		return (5);
	}
	ft_putstr_fd_pf("0x", fd);
	count += ft_putnbr_base_x(n, 0, fd);
	return (count + 2);
}
