/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:25:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/26 05:54:19 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"

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
		ft_strlcpy(env->variable, &(envp[i][med]), len - med + 1);
		env = env->next;
		i++;
	}
	return (0);
}

static void	clean_env(t_env **env)
{
	t_env	*tmp;
	t_env	*lst;

	tmp = NULL;
	lst = *env;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->variable)
			free(tmp->variable);
		if (tmp)
			free(tmp);
	}
	*env = NULL;
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

static int	list_init(t_env **env, char **envp)
{
	int		i;
	t_env	*lst;
	t_env	*tmp;

	i = 0;
	lst = *env;
	tmp = NULL;
	while (envp[i])
	{
		tmp = env_init();
		if (!tmp)
			return (1);
		if (!lst)
		{
			*env = tmp;
			lst = *env;
		}
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

int	get_env(char **envp, t_env **ptr_env)
{
	int		ret;

	ret = list_init(ptr_env, envp);
	if (!ret)
		ret = var_env_malloc_init(*ptr_env, envp);
	if (ret)
		clean_env(ptr_env);
	return (ret);
}
