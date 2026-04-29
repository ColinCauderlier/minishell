/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/29 18:06:43 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	ft_fprintf(int fd, const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			count += ft_fprintf_checktype(format[i + 1], args, fd);
			i++;
		}
		else
		{
			ft_fprintf_putchar_fd_pf(format[i], fd);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
