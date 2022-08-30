/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:44:20 by mjallada          #+#    #+#             */
/*   Updated: 2022/08/30 18:49:34 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int s)
{
	char	*str2;
	int		len;

	len = ft_strlen(str);
	str2 = (char *)str;
	while (len > 0)
	{
		if (*str2 == (char)s)
			return (str2);
		str2++;
		len--;
	}
	return (NULL);
}
