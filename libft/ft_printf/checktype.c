/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:16:23 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/27 13:14:26 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	checktype(char c, va_list args, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd_pf(va_arg(args, int), fd));
	else if (c == 's')
		return (ft_putstr_fd_pf(va_arg(args, char *), fd));
	else if (c == 'p')
		return (ft_putpointer(va_arg(args, unsigned long), fd));
	else if ((c == 'd') || (c == 'i'))
		return (ft_putnbr_t_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (ft_putnbr_t_fd(va_arg(args, unsigned int), fd));
	else if (c == 'x')
		return (ft_putnbr_base_x(va_arg(args, unsigned int), 0, fd));
	else if (c == 'X')
		return (ft_putnbr_base_x(va_arg(args, unsigned int), 1, fd));
	else if (c == '%')
		return (ft_putchar_fd_pf('%', 1));
	else
		return (0);
}
