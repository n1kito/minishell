/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:06:19 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 14:54:21 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*memoryblock;

	len = ft_strlen(s);
	memoryblock = malloc(sizeof(*memoryblock) * (len + 1));
	if (memoryblock == 0)
		return (NULL);
	i = 0;
	while (i < len)
	{
		memoryblock[i] = s[i];
		i++;
	}
	memoryblock[i] = 0;
	return (memoryblock);
}
