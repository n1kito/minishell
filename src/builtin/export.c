/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/03 17:37:10 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_variable(char *str, int i, int j)
{
	char	*variable;

	if (i == 0 || j == 0 || j - i <= 0)
		return (NULL);
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
	t_env	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_env *));
	if (!new)
		return ;
	new->next = NULL;
	while (env->next)
		env = env->next;
	env->next = new;
	while (variable[i] && variable[i - 1] != '=')
		i++;
	while (variable[j])
		j++;
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
