/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:18:40 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 14:35:06 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destination;
	const char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (char *)dest;
	source = (char *)src;
	i = 0;
	if (destination > source)
		while (n--)
			destination[n] = source[n];
	else
		while (i++ < n)
			destination[i - 1] = source[i - 1];
	return (dest);
}
