/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:14:34 by mjallada          #+#    #+#             */
/*   Updated: 2021/12/02 11:46:56 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int checkme)
{
	if (checkme >= 48 && checkme <= 57)
		return (1);
	else if (checkme >= 65 && checkme <= 90)
		return (1);
	else if (checkme >= 97 && checkme <= 122)
		return (1);
	else
		return (0);
}
