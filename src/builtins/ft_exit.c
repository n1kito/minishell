/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:12:00 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/13 01:30:22 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_above_atoll(char const *str, int neg)
{
	int		ret;
	char	*max_int;

	ret = 0;
	max_int = "9223372036854775807";
	if (ft_strlen(str) > ft_strlen(max_int))
		ret = 1;
	if (ft_strlen(str) < ft_strlen(max_int))
		return (0);
	while (ret == 0 && *(max_int + 1))
	{
		if (*str < *max_int)
			ret = 0;
		if (*str > *max_int)
			ret = 1;
		if (*str < *max_int || *str > *max_int)
			break;
		str++;
		max_int++;
	}
	if (neg && ret == 0 && *str > 8)
		ret = 1;
	if (!neg && ret == 0 && *str > 7)
		ret = 1;
	return (ret);
}

static void	check_arg1_is_valid(char *variable)
{
	int	i;
	int	neg;

	neg = 0;
	i = 0;
	while (*variable == ' ' || (*variable >= 9 && *variable <= 13))
		variable++;
	if (*variable == '=' || *variable == '-')
	{
		if (*variable == '-')
			neg = 1;
		variable++;
	}
	while (variable[i] <= '9' && variable[i] >= '0')
		i++;
	if (variable[i] || is_above_atoll(variable, neg))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_minishexit = 2;
		exit(2);
	}
}

long int    ft_atoll(const char *nptr)
{
	long long int    num;
	int            sign;
	int            i;

	num = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = (num * 10) + (nptr[i] - 48);
		i++;
	}
	return (num * sign);
}

void	ft_exit(t_master *master, int cmd_index)
{
	char	**variable;

	variable = master->commands[cmd_index]->cmd_array;
	if (master->cmd_count == 1) 
	{
		ft_putstr_fd("exit\n", 0);
		close_files(master, cmd_index);
		close_pipes(master);
	}
	if (variable[1])
		check_arg1_is_valid(variable[1]);
	else if (variable[1] && variable[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_minishexit = 1;
		return ;
	}
	else if (variable[1])
		exit(ft_atoll(variable[1]));
	exit(free_all(master, g_minishexit));
}
