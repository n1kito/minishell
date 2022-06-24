/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:05:23 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 11:51:30 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destination;
	const char	*source;

	if (!dest && !src)
		return (NULL);
	i = 0;
	destination = dest;
	source = src;
	while (i < n)
	{
		*destination = *source;
		destination++;
		source++;
		i++;
	}
	return (dest);
}
