/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:56:41 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 16:57:59 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env, char **arg)
{
	t_env	*tmp;

	tmp = env;
	g_minishexit = 0;
	if (arg[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd("': No such file or directory\n ", 2);
		g_minishexit = 127;
	}
	else
	{
		while (tmp)
		{
			if (tmp->name && tmp->is_env)
			{
				printf("%s=", tmp->name);
				if (tmp->variable)
					printf("%s", tmp->variable);
				printf("\n");
			}
			tmp = tmp->next;
		}
	}
}
