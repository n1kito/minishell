/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/26 05:58:17 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

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

static void	ft_print_error(char *variable)
{
	write (2, "Unset: Error:", 19);
	write (2, variable, ft_strlen(variable));
	write (2, " not a valid identifier\n", 26);
}

static t_env	*unset_middle(t_env *env, t_env *start)
{
	while (start->next != env)
		start = start->next;
	start->next = env->next;
	free(env->name);
	if (env->variable)
		free(env->variable);
	env->is_env = 0;
	if (env)
		free(env);
	return (start);
}

int	ft_unset(t_env *env, char **arg)
{
	int		i;
	int		ret;
	t_env	*start;

	i = 0;
	ret = 0;
	start = env;
	while (arg[i])
	{
		if (arg_is_ok_for_env(arg[i]) == 0)
		{
			while (check_match(start->name, arg[i]) && env)
			{
				start = start->next;
				env->next = start->next;
				start->next = env;
				env = unset_middle(env, start);
			}
			while (env)
			{
				if (check_match(env->name, arg[i]))
					env = unset_middle(env, start);
				env = env->next;
			}
		}
		else
		{
			ft_print_error(arg[i]);
			ret = 1;
		}
		i++;
		env = start;
	}
	return (ret);
}
