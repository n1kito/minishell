/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:36:25 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/16 04:11:31 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_printf(char *to_print)
{
	if (write(1, to_print, ft_strlen(to_print)) == -1)
		g_minishexit = 1;
}

int	arg_is_ok_for_env(char const *str, int exprt)
{
	int	i;

	i = 1;
	if (!str[0])
		return (2);
	if (str[0] == '_' && !ft_isalnum(str[1]) && str[1] != '_')
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i])
	{
		if (exprt)
		{
			if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
				return (0);
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	check_malloc_in_builtin(t_master *master, t_env *env)
{
	int	command;

	command = master->cmd_count;
	if (!env || !env->name)
	{
		write(2, "Minishell failure: malloc error in builtin cd\n", 47);
		free_all(master, g_minishexit);
		exit(1);
	}
	if (!env->variable)
	{
		write(2, "Minishell failure: malloc error in builtin cd\n", 47);
		free_all(master, g_minishexit);
		exit(1);
	}
}

void	exit_env_printer(t_master *master)
{
	write(2, "Minishell: export: malloc fail\n", 50);
	if (master->cmd_count > 1)
		exit(free_all(master, 42));
	exit(free_all(master, 1));
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
