/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:12:00 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/16 03:23:42 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_above_atoll(char const *str, int neg)
{
	int		i;
	char	*max_int;

	i = 0;
	max_int = "9223372036854775807";
	if (ft_strlen(str) > ft_strlen(max_int))
		return (1);
	if (ft_strlen(str) < ft_strlen(max_int))
		return (0);
	while (max_int[i + 1] && max_int[i])
	{
		if (str[i] < max_int[i])
			return (0);
		if (str[i] > max_int[i])
			return (1);
		i++;
	}
	if (neg == 1 && str[i] > '8')
		return (1);
	if (neg == 0 && str[i] > '7')
		return (1);
	return (0);
}

static void	check_arg1_is_valid(t_master *master, char *var)
{
	int	i;
	int	j;
	int	neg;

	neg = 0;
	i = 0;
	j = 0;
	while (*(var + j) == ' ' || (*(var + j) >= 9 && *(var + j) <= 13))
		j++;
	if (*(var + j) == '=' || *(var + j) == '-' || *(var + j) == '+')
	{
		if (*(var + j) == '-')
			neg = 1;
		j++;
	}
	while ((var + j)[i] <= '9' && (var + j)[i] >= '0')
		i++;
	if ((var + j)[i] || is_above_atoll((var + j), neg))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_minishexit = 2;
		exit(free_all(master, 2));
	}
}

long long int	ft_atoll(const char *nptr)
{
	long long int	num;
	int				sign;
	int				i;

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
		check_arg1_is_valid(master, variable[1]);
	if (variable[1] && variable[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_minishexit = 1;
		return ;
	}
	else if (variable[1])
		exit(free_all(master, ft_atoll(variable[1])));
	exit(free_all(master, g_minishexit));
}
