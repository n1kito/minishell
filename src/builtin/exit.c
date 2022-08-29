/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:12:00 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/29 22:02:47 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_is_num(char	*str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **variable)
{
	ft_putendl_fd("exit", 2);
	if (!variable[1])
		exit (0);
	else if (variable[2])
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (2);
	}
	else if (!ft_is_num(variable[1]))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(variable[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else
		exit(ft_atoi(variable[1]));
	return (0);
}
