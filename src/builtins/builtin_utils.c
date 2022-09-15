/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:36:25 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/14 23:35:35 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

void	safe_printf(char *to_print)
{
	if (write(1, to_print, ft_strlen(to_print)) == -1)
		g_minishexit = 1;
}

int	arg_is_ok_for_env(char const *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (2);
	if ((str[0] == '_' && (str[1] == '+' || str[1] == '=')))
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (0);
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
		if (command > 1)
			exit(42);
		exit(1);
	}
	if (!env->variable)
	{
		write(2, "Minishell failure: malloc error in builtin cd\n", 47);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
}
