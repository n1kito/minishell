/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:04:10 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/23 18:02:50 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function destroys the char** that has been created for the excutiom
// This function is noly executed if there is a malloc problem

static void	destroy_env(char **envp, int lim)
{
	int	i;

	i = 0;
	while (i < lim)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

// This functions counts the number of elements in the env linked list

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

// This functions takes a linked list where the env is stored
// It transforms it into a char** for the sake of the execution
// It stores the pointer in the master struct
// It returns 0 in case of a success and 1 in case of a failure

int	env_for_exe(t_master *master)
{
	int		i;
	char	**envp;

	i = 0;
	envp = malloc(sizeof(char *) * count_env(master->env));
	if (!envp)
		return (1);
	while (env)
	{
		envp[i] = malloc(sizeof(char) * (ft_strlen(master->env->name)
			+ ft_strlen(env->variable) + 1));
		if (!envp[i])
		{
			ft_destroy_env(envp, i);
			return (1);
		}
		ft_strlcpy(envp[i], master->env->name, ft_strlen(master->env->name));
		ft_strlcat(envp[i], master->env->variable, \
			ft_strlen(master->env->variable));
		i++;
		env = env->next;
	}
	master->env_array = envp;
	return (0);
}
