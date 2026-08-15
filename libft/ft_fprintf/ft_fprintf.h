/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucinguy <lucinguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:15:00 by lucinguy          #+#    #+#             */
/*   Updated: 2026/04/29 18:06:46 by lucinguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_fprintf(int fd, const char *format, ...);

int		ft_fprintf_checktype(char c, const va_list args, int fd);

size_t	ft_fprintf_putchar_fd_pf(char c, int fd);
size_t	ft_fprintf_putstr_fd_pf(const char *s, int fd);

int		ft_fprintf_putnbr_t_fd(long n, int fd);
int		ft_fprintf_putnbr_base_x(unsigned long n, int uppercase, int fd);
int		ft_fprintf_putpointer(unsigned long n, int fd);

#endif