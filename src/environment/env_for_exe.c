/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:52:28 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/13 17:57:29 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_malloc_fo_env_exe(t_master *master, char **array, int depth)
{
	int	command;

	command = master->cmd_count;
	if (!array)
	{
		write(2, "Minishell failure: malloc error in env_for_exe\n", 48);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
	if (!(*array) && depth)
	{
		write(2, "Minishell failure: malloc error in env_for_exe\n", 48);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
}

/* This function destroys the char** that has been created for the excutiom
 * This function is noly executed if there is a malloc problem. */
void	ft_destroy_env(t_master *master)
{
	char	**env_array;
	int		i;

	env_array = master->env_for_exec;
	i = 0;
	while (env_array && env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	master->env_for_exec = NULL;
}

/* This functions counts the number of elements in the env linked list. */
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

/* This functions takes a linked list where the env is stored
 * It transforms it into a char** for the sake of the execution
 * It stores the pointer in the master struct
 * It returns 0 in case of a success and 1 in case of a failure. */
int	env_for_exe(t_master *master)
{
	int		i;
	char	*tmp;
	t_env	*env;
	char	**array;

	i = 0;
	env = master->env;
	array = ft_calloc(count_env(env) + 1, sizeof(char *));
	check_malloc_fo_env_exe(master, array, 0);
	while (env)
	{
		if (env->is_env)
		{
			array[i] = ft_strjoin(env->name, "=");
			check_malloc_fo_env_exe(master, &array[i], 1);
			tmp = array[i];
			array[i] = ft_strjoin(array[i], env->variable);
			free(tmp);
			check_malloc_fo_env_exe(master, &array[i], 1);
		}
		env = env->next;
		i++;
	}
	master->env_for_exec = array;
	return (1);
}
