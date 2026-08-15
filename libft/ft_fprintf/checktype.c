/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/29 18:06:25 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprintf_checktype(char c, const va_list args, int fd)
{
	if (c == 'c')
		return (ft_fprintf_putchar_fd_pf(va_arg(args, int), fd));
	else if (c == 's')
		return (ft_fprintf_putstr_fd_pf(va_arg(args, char *), fd));
	else if (c == 'p')
		return (ft_fprintf_putpointer(va_arg(args, unsigned long), fd));
	else if ((c == 'd') || (c == 'i'))
		return (ft_fprintf_putnbr_t_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (ft_fprintf_putnbr_t_fd(va_arg(args, unsigned int), fd));
	else if (c == 'x')
		return (ft_fprintf_putnbr_base_x(va_arg(args, unsigned int), 0, fd));
	else if (c == 'X')
		return (ft_fprintf_putnbr_base_x(va_arg(args, unsigned int), 1, fd));
	else if (c == '%')
		return (ft_fprintf_putchar_fd_pf('%', fd));
	else
		return (0);
}
