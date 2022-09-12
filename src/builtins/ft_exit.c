/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:12:00 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 16:34:32 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (variable[1] && !ft_is_num(variable[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(variable[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_minishexit = 2;
	}
	else if (variable[1] && variable[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_minishexit = 1;
		return ;
	}
	else if (variable[1])
		g_minishexit = ft_atoi(variable[1]);
	exit(free_all(master, g_minishexit));
}
