/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:48:22 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 17:31:52 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	c1 = (unsigned char *)first;
	c2 = (unsigned char *)second;
	while (length--)
	{
		if (!c1[i] || !c2[i] || c1[i] != c2[i])
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}
