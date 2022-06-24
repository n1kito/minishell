/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:06:32 by mjallada          #+#    #+#             */
/*   Updated: 2022/05/04 11:06:34 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str != '%')
			count += ft_putchar_fd(*(str), fd);
		else
			count += ft_parameter_gps(fd, *(++str), args);
		str++;
	}
	va_end(args);
	return (count);
}

int	ft_parameter_gps(int fd, char format, va_list args)
{
	unsigned long int	arg_p;

	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	else if (format == 'u')
		return (ft_putnbr_fd(va_arg(args, unsigned int), fd));
	else if (format == 'x' || format == 'X')
		return (ft_puthexa_fd(fd, va_arg(args, unsigned int), format));
	else if (format == 'p')
	{
		arg_p = va_arg(args, unsigned long int);
		if (arg_p == 0)
			return (ft_putstr_fd(PTR_NULL, fd));
		else
		{
			write(fd, "0x", 2);
			return (ft_puthexa_fd(fd, arg_p, format) + 2);
		}
	}
	else
		return (ft_putchar_fd(format, fd));
}

int	ft_puthexa_fd(int fd, unsigned long int nbr, char format)
{
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_puthexa_fd(fd, nbr / 16, format);
		count += ft_puthexa_fd(fd, nbr % 16, format);
	}
	else
	{
		if (nbr <= 9)
			count += ft_putchar_fd(nbr + '0', fd);
		else
		{
			if (format == 'x' || format == 'p')
				count += ft_putchar_fd(nbr - 10 + 'a', fd);
			else if (format == 'X')
				count += ft_putchar_fd(nbr - 10 + 'A', fd);
		}
	}
	return (count);
}
