/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:25:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/22 23:45:58 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// This functions gives the number of env variables
// It works similarly to the strlen function

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// This function takes the linked list and writes the env variables in it
// the first string called NAME takes the beggininning of the string until the =
// the second string VARIABLE takes the rest of the string

void	env_write(t_env *env, char **envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (envp[i] && env)
	{
		j = 0;
		k = 0;
		while (envp[i][j] && envp[i][j - 1] != '=')
			env->name[k++] = envp[i][j++];
		env->name[k] = '\0';
		k = 0;
		while (envp[i][j])
			env->variable[k++] = envp[i][j++];
		env->variable[k] = '\0';
		env = env->next;
		i++;
	}
}

// This function initializes the 2 strings used to store the name and the var
// It allocates sufficient memory for them to accomodate the strings

void	var_env_malloc_init(t_env *env, char **envp)
{
	int	i;
	int	med;
	int	len;

	i = 0;
	while (env)
	{
		med = 0;
		len = 0;
		while (envp[i][len])
			len++;
		while (envp[i][med] != '=')
			med++;
		env->name = malloc(sizeof(char) * med + 1);
		if (!env->name)
			return ;
		env->variable = malloc(sizeof(char) * len - med + 1);
		if (!env->variable)
			return ;
		env->is_env = 1;
		env = env->next;
		i++;
	}
}

// This function initializes the linked list
// This list will be used to store the environment

t_env	*list_init(int depth)
{
	t_env	*new;

	if (depth <= 0)
		return (NULL);
	new = malloc(sizeof(t_env *));
	if (!new)
		return (NULL);
	new->next = list_init(depth - 1);
	return (new);
}

// This function takes the environment given as an argument
// It then transforms it into a linked list with
// It then returns a pointer to the first element of the list

t_env	*get_env(char **envp)
{
	int		len;
	t_env	*env;

	len = env_len(envp);
	env = list_init(len);
	var_env_malloc_init(env, envp);
	env_write(env, envp);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env *env;

	(void)argc;
	(void)argv;
	env = get_env(envp);
	while (env)
	{
		printf("%s",env->name);
		printf("%s\n",env->variable);
		env = env->next;
	}
	return (0);
}
