/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/24 20:11:41 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static void	add_to_env(t_env *env, char *str)
{
	int		i;
	int		j;
	t_env	*new;

	i = 0;
	j = 0;
	new = NULL;
	while (env->next)
		env = env->next;
	while (str[i] && str[i - 1] != '=')
		i++;
	while (str[j])
		j++;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->next = NULL;
	env->next = new;
	new->name = add_name(str, i);
	if (new->name)
		new->variable = add_variable(str, i, j);
}

static void	update_env(t_env *env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i - 1] != '=')
		i++;
	while (str[j])
		j++;
	if (env->variable)
		free(env->variable);
	env->variable = add_variable(str, i, j);
}

static void	check_if_in_env(t_env *env, char *str)
{
	int		i;
	t_env	*save;
	t_env	*check;

	i = 0;
	save = env;
	check = NULL;
	while (str[i] && str[i - 1] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(str, env->name, i) == 0 && ft_strlen(env->name) == i)
			check = env;
		env = env->next;
	}
	if (check)
		update_env(check, str);
	else
		add_to_env(save, str);
}

int	ft_export(t_env *env, char **variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		check_if_in_env(env, variable[i]);
		i++;
	}
	return (0);
}
