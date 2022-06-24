/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:26:37 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/08 21:02:04 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementcount, size_t elementsize)
{
	void	*memoryblock;

	memoryblock = malloc(elementcount * elementsize);
	if (!memoryblock)
		return (0);
	ft_bzero(memoryblock, elementcount * elementsize);
	return (memoryblock);
}
