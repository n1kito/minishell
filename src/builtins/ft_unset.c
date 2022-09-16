/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/16 03:01:03 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_match(char *name, char *arg)
{
	if (ft_strncmp(name, arg, ft_strlen(arg)) == 0)
	{
		if (ft_strlen(name) == ft_strlen(arg))
			return (1);
	}
	return (0);
}

static int	ft_print_error(char *variable)
{
	write (2, "Unset: Error: \"", 15);
	write (2, variable, ft_strlen(variable));
	write (2, "\" not a valid identifier\n", 26);
	return (1);
}

static t_env	*unset_middle(t_env *env, t_env *start)
{
	while (start && start->next != env)
		start = start->next;
	if (env->next)
		start->next = env->next;
	else
		start->next = NULL;
	if (env->name)
		free(env->name);
	if (env->variable)
		free(env->variable);
	env->is_env = 0;
	if (env)
		free(env);
	return (start);
}

static t_env	*ft_swap(t_env *env)
{
	t_env	*tmp;
	t_env	*start;

	start = env->next;
	tmp = env;
	if (env->name)
	{
		free(tmp->name);
		tmp->name = NULL;
	}
	if (tmp->name)
	{
		free(tmp->name);
		tmp->name = NULL;
	}
	tmp->next = NULL;
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (start);
}

void	ft_unset(t_env **env, char **arg)
{
	int		i;
	t_env	*start;

	i = 1;
	start = *env;
	g_minishexit = 0;
	while (arg[i] && *env)
	{
		if (arg_is_ok_for_env(arg[i]) == 0 && *env)
		{
			while (check_match((*env)->name, arg[i]))
			{
				start = ft_swap(start);
				*env = start;
			}
			while (*env && !check_match((*env)->name, arg[i]))
				*env = (*env)->next;
			if (*env)
				*env = unset_middle(*env, start);
		}
		else if (arg_is_ok_for_env(arg[i]) == 1)
			g_minishexit = ft_print_error(arg[i]);
		i++;
		*env = start;
	}
}
