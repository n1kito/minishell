/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/25 02:51:23 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static t_env	*unset_first(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	env = env->next;
	free(tmp->name);
	if (tmp->variable)
		free(tmp->variable);
	free(tmp);
	return (env);
}

static int	check_match(char *name, char *arg)
{
	if (ft_strncmp(name, arg, ft_strlen(arg)) == 0)
	{
		if (name[ft_strlen(name) - 1] == '=' \
			&& ft_strlen(name) == ft_strlen(arg) + 1)
			return (1);
		else if (ft_strlen(name) == ft_strlen(arg))
			return (1);
	}
	return (0);
}

static t_env	*unset_middle(t_env *env, t_env *start)
{
	while (start->next != env)
		start = start->next;
	start->next = env->next;
	free(env->name);
	if (env->variable)
		free(env->variable);
	free(env);
	return (start);
}

int	ft_unset(t_env *env, char **arg)
{
	int		i;
	t_env	*start;

	i = 0;
	start = env;
	while (arg[i])
	{
		if (check_match(start->name, arg[i]) && env)
		{
			env = unset_first(env);
			start = env;
		}
		env = env->next;
		while (env)
		{
			if (check_match(env->name, arg[i]))
				env = unset_middle(env, start);
			env = env->next;
		}
		++i;
		env = start;
	}
	return (0);
}
