/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:31:26 by lucinguy          #+#    #+#             */
/*   Updated: 2025/11/27 13:53:12 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
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
			count += checktype(format[i + 1], args, 1);
			i++;
		}
		else
		{
			ft_putchar_fd_pf(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char			c;
// 	char			*s;
// 	int				*p;
// 	int				d;
// 	int				i;
// 	unsigned int	u;
// 	unsigned int	x;
// 	unsigned int	X;
// 	int				result1;
// 	int				test1;
// 	int				result2;
// 	int				test2;

// 	c = 'a';
// 	s = "Lorem";
// 	d = -2147483648;
// 	p = &d;
// 	i = 2147483647;
// 	u = 5904375;
// 	x = 9084324;
// 	X = 9840394;
// 	result1 = printf("1 :\nc = %c\ns = %s\np = %p\nd = %d\n", c, s, p, d);
// 	result2 = printf("2 :\ni = %i\nu = %u\nx = %x\nX = %X\n%%\n", i, u, x, X);
// 	printf("-------------------------\n");
// 	test1 = ft_printf("1 :\nc = %c\ns = %s\np = %p\nd = %d\n", c, s, p, d);
// 	test2 = ft_printf("2 :\ni = %i\nu = %u\nx = %x\nX = %X\n%%\n", i, u, x, X);
// 	printf("-------------------------\n");
// 	printf("Nb : P1 = %d | P2 = %d (printf original)\n", result1, result2);
// 	ft_printf("Nb* : P1 = %d | P2 = %d (printf perso)\n", test1, test2);
// }
