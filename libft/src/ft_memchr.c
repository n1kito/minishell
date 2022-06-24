/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:51:28 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 14:44:49 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memblock, int searchedchar, size_t size)
{
	char		searchme;
	const char	*position;

	position = memblock;
	searchme = (char)searchedchar;
	while (size > 0)
	{
		if (*position == searchme)
			return ((char *)position);
		position++;
		size--;
	}
	return (NULL);
}
