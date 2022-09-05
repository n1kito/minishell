/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:12:00 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 11:36:02 by vrigaudy         ###   ########.fr       */
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

void	ft_exit(char **variable)
{
	ft_putstr_fd("exit\n", 0);
	if (!variable[1])
	{
		g_minishexit = 0;
		exit(g_minishexit);
	}
	else if (!ft_is_num(variable[1]))
	{
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(variable[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_minishexit = 2;
		exit(g_minishexit);
	}
	else if (variable[2])
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		g_minishexit = 1;
	}
	else
	{
		g_minishexit = ft_atoi(varibale[1])
		exit(g_minishexit);
	}
}
