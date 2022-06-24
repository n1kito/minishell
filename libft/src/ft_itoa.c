/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:05:32 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/09 11:51:42 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(long long int n)
{
	int			count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_n_is_zero(char *out)
{
	out[0] = '0';
	out[1] = '\0';
	return (out);
}

char	*ft_itoa(int n)
{
	char			*out;
	int				len;
	long long int	n2;

	n2 = n;
	len = ft_count_digit(n2);
	out = malloc(sizeof(*out) * (len + 1));
	if (!out)
		return (NULL);
	out[len] = '\0';
	if (n2 == 0)
		return (ft_n_is_zero(out));
	if (n2 < 0)
	{
		out[0] = '-';
		n2 *= -1;
	}
	while (n2 > 0)
	{
		out[len - 1] = (n2 % 10) + 48;
		n2 = n2 / 10;
		len--;
	}
	return (out);
}
