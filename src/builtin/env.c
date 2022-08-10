/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 00:56:41 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/10 19:39:48 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	env(t_env *env)
{
	while (env)
	{
		if (env->name && env->variable)
			printf("%s%s\n", env->name, env->variable);
		env = env->next;
	}
	return (0);
}
