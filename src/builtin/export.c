/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/07 12:35:49 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_variable(char *str, int i, int j)
{
	char	*variable;

	if (i == 0 || j == 0 || j - i <= 0)
		return (NULL);
	variable = malloc(sizeof(char) * j - i + 1);
	if (!variable)
		return (NULL);
	while (*(str - 1) != '=')
		str++;
		return (NULL);
	ft_strlcpy(variable, str, j - i);
	return (variable);
}

static char	*add_name(char *str, int i)
{
	char	*name;

	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, i);
	return (name);
}

static void	add_to_env(t_env *env, char *variable)
{
	int		i;
	int		j;
	int		exist;
	t_env	*new;
	t_env	*save;

	i = 0;
	j = 0;
	exist = 0;
	save = env;
	new = NULL;
	while (variable[i] && variable[i - 1] != '=')
		i++;
	while (variable[j])
		j++;
	while (env)
	{
		if (ft_strncmp(env->name, variable, i) == 0\
			&& ft_strlen(env->name) == 1)
			exist = 1;
		env = env->next;
	}
		if
	new = malloc(sizeof(t_env *));
	if (!new)
		return ;
	new->next = NULL;
	env->next = new;
	env->name = add_name(variable, i);
	if (env->name)
		env->variable = add_variable(variable, i, j);
}

int	export(t_env *env, char **variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		add_to_env(env, variable[i]);
		i++;
	}
	return (0);
}
