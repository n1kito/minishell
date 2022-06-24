/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:28:24 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/07 15:04:34 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searched)
{
	int	i;

	i = ft_strlen(string);
	while (i >= 0)
	{
		if (string[i] == (char)searched)
			return ((char *)string + i);
		i--;
	}
	return (NULL);
}
