/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:50:25 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 23:50:28 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compares two strings, returns 0 if they are identical,
 * otherwise returns difference between the firt two
 * different characters. Returns -1 if one of the strings
 * is NULL. */
int	ft_strcmp(const char *first, const char *second)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	if (!first || !second)
		return (-1);
	if (ft_strlen(first) != ft_strlen(second))
		return (-1);
	c1 = (unsigned char *)first;
	c2 = (unsigned char *)second;
	i = 0;
	while (c1[i] && c2[i])
	{
		if (c1[i] != c2[i])
			return (-1);
		i++;
	}
	return (0);
}
