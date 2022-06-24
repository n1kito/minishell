/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 07:52:42 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 11:47:15 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int tocheck)
{
	if (tocheck >= 65 && tocheck <= 90)
		return (1);
	if (tocheck >= 97 && tocheck <= 122)
		return (1);
	else
		return (0);
}
