/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:20:42 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/03 15:47:35 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nbr, int fd)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count += ft_putchar_fd('-', fd);
	}
	if (nbr < 10)
		count += ft_putchar_fd(nbr + '0', fd);
	else
	{
		count += ft_putnbr_fd(nbr / 10, fd);
		count += ft_putnbr_fd(nbr % 10, fd);
	}
	return (count);
}
