/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:09:37 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 11:52:02 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *position, int character, size_t length)
{
	char	*str;
	size_t	i;

	i = 0;
	str = position;
	while (i < length)
	{
		*str = character;
		str++;
		i++;
	}
	return (position);
}
