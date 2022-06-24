/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:57:32 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 15:13:09 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	if (size == 0)
		return (ft_strlen(source));
	if (size < i)
	{
		i = 0;
		while (source[i])
			i++;
		return (size + i);
	}
	while (i < (size - 1) && source[j])
		dest[i++] = source[j++];
	dest[i] = 0;
	while (source[j++])
		i++;
	return (i);
}
