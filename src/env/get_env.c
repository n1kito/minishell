/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:25:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/25 04:08:08 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

// This function initializes the 2 pointers used to store the name and the var
// It allocates sufficient memory for them to accomodate the strings
// This function takes the linked list and writes the env variables in it
// the first string called NAME takes the beggininning of the string until the =
// the second string VARIABLE takes the rest of the string

static int	var_env_malloc_init(t_env *env, char **envp)
{
	int		i;
	int		med;
	int		len;

	i = 0;
	while (env)
	{
		med = 0;
		len = 0;
		while (envp[i][len])
			len++;
		while (envp[i][med - 1] != '=' && envp[i][med])
			med++;
		env->name = malloc(sizeof(char) * med + 1);
		env->variable = malloc(sizeof(char) * len - med + 1);
		if (!env->variable || !env->name)
			return (1);
		ft_strlcpy(env->name, envp[i], med + 1);
		ft_strlcpy(env->variable, envp[i][med], len - med + 1);
		env = env->next;
		i++;
	}
	return (0);
}

static void	clean_env(t_master *master)
{
	t_env	*tmp;
	t_env	*lst;

	tmp = NULL;
	lst = master->env;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->variable)
			free(tmp->variable);
		free(tmp)
	}
	master->env = NULL;
}

static t_env	*env_init(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_env));
	new->is_env = 1;
	return (new);
}

// This function initializes the linked list
// This list will be used to store the environment

static int	list_init(t_master *master, char **envp)
{
	int		i;
	t_env	*tmp;
	t_env	*lst;

	i = 0;
	tmp = NULL;
	lst = master->env;
	while (envp[i])
	{
		tmp = env_init();
		if (!tmp)
			return (1);
		if (!lst)
			master->env = tmp;
		else
		{
			lst->next = tmp;
			lst = lst->next;
		}
		i++;
	}
	return (0);
}


// This function takes the environment given as an argument
// It then transforms it into a linked list with
// It then returns a pointer to the first element of the list

int	get_env(char **envp, t_master *master)
{
	int		ret;
	t_env	*env;

	ret = list_init(master, envp);
	if (ret)
	{
		clean_env(master);
		return (ret);
	}
	ret = var_env_malloc_init(master->env, envp);
	if (ret)
	{
		clean_env(master);
		return (ret);
	}
	return (ret);
}
