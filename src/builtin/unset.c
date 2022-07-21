/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/21 18:14:21 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*unset_first(t_env *env)
{
	t_env	*temp;

	temp = env;
	env = env->next;
	free(temp->name);
	free(temp->variable);
	free(temp->next);
	free(temp);
	return (env);
}

int	unset(t_env *env, char *str)
{
	t_env	*temp;

	if (ft_strncmp(env->name, str, ft_strlen(str)) == 0
		&& ft_strlen(env->name) - 1 == ft_strlen(str))
		env = unset_first(env);
	temp = env;
	while (env)
	{
		if (ft_strncmp(env->name, str, ft_strlen(str)) == 0
			&& ft_strlen(env->name) - 1 == ft_strlen(str))
		{
			temp->next = env->next;
			free(env->name);
			free(env->variable);
			free(env->next);
			free(env);
		}
		temp = env;
		env = env->next;
	}
	return (0);
}
