/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:04:10 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/14 17:59:18 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This functions takes a linked list where the env is stored
// It transforms it into a char** for the sake of the execution

char **env_for_exe(t_env *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = malloc(sizeof(char *));
	if (!envp)
		return (NULL);
	while (env)
	{
		*(envp + i) = malloc(sizeof(char) * (ft_strlen(env->name)
			+ ft_strlen(env->variable) + 1));
		if (!*(envp + i))
			return (NULL);
		ft_strlcpy(*(envp + i), env->name, ft_strlen(env->name));
		ft_strlcat(*(envp + i), env->variable, ft_strlen(env->variable));
		env = env->next;
		i++;
	}
	return (envp);
}
