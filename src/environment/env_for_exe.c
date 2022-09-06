/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:04:10 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/06 14:46:08 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function destroys the char** that has been created for the excutiom
// This function is noly executed if there is a malloc problem
static int	ft_destroy_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (0);
}

// This functions counts the number of elements in the env linked list
static int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->is_env)
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
	char	*tmp;
	int		len;
	t_env	*env;
	char	**array;

	i = 0;
	env = master->env;
	len = count_env(env);
	ft_destroy_env(master->env_array);
	array = ft_calloc(len + 1, sizeof(char *));
	if (!array)
		return (0);
	while (env)
	{
		if (env->is_env)
		{
			array[i] = ft_strjoin(env->name, "=");
			if (!array[i])
				return (ft_destroy_env(array));
			tmp = array[i];
			array[i] = ft_strjoin(array[i], env->variable);
			free(tmp);
			if (!array[i])
				return (ft_destroy_env(array));
		}
		env = env->next;
		i++;
	}
	master->env_array = array;
	return (1);
}
