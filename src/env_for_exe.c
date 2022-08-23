/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:47:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/23 14:51:34 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This functions takes a linked list where the env is stored
// It transforms it into a char** for the sake of the execution

static int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	env_for_exe(t_master *master)
{
	int		i;
	char	**envp;

	i = 0;
	envp = malloc(sizeof(char *) * count_env(env));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = malloc(sizeof(char) * (ft_strlen(env->name)
			+ ft_strlen(env->variable) + 1));
		if (!envp[i])
			return (NULL);
		ft_strlcpy(envp[i], env->name, ft_strlen(env->name));
		ft_strlcat(envp[i], env->variable, ft_strlen(env->variable));
		i++;
		env = env->next;
	}
	return (envp);
}
