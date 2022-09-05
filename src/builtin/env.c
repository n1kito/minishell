/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:56:41 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 10:54:35 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->is_env == 1)
		{
			if (env->name)
			{
				printf("%s=", env->name);
				if (env->variable)
					printf("%s", env->variable);
				printf("\n");
			}
		}
		env = env->next;
	}
	g_minishexit = 0;
}
