/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 14:01:08 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(t_env *env, char *str)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = NULL;
	while (ft_strncmp(str, env->name, ft_strlen(env->name)) != 0 \
			|| ft_strlen(env->name) != i)
		env = env->next;
	while (str[i] && str[i - 1] != '=')
		i++;
	if (str[i])
	{
		if (str[i - 2] && str[i - 2] == '+' && str[i - 1] == '=')
		{
			tmp = env->variable;
			env->variable = ft_strjoin(tmp, &str[i]);
			free(tmp);
		}
		else if (str[i - 1] && str[i - 1] == '=')
		{
			free(env->variable);
			env->variable = ft_strdup(&str[i]);
		}
		env->is_env = 1;
	}
	if (!env->variable)
		return (0);
	return (1);
}

static int	add_elem_to_env(t_env *env, char *str)
{
	int		i;
	t_env	*new;

	i = 0;
	while (env->next)
		env = env->next;
	while (str[i] && str[i - 1] != '=')
		i++;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (0);
	if (str[i])
		new->is_env = 1;
	new->name = malloc(sizeof(char) * (i + 1));
	if (!new->name)
		return (0);
	if (str[i])
	{
		new->variable = ft_strdup(&str[i]);
		if (!new->variable)
			return (0);
	}
	ft_strlcat(new->name, str, i + 1);
	env->next = new;
	return (1);
}

static int	check_if_in_env(t_env *env, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i - 1] != '=')
		i++;
	while (env)
	{
		if (ft_strncmp(str, env->name, ft_strlen(env->name)) == 0 \
			&& ft_strlen(env->name) == i)
			return (1);
		env = env->next;
	}
	return (0);
}

int	arg_is_ok_for_env(char const *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_env **env, char **variable)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	g_minishexit = 0;
	while (variable[i])
	{
		if (arg_is_ok_for_env(variable[i]) == 0)
		{
			if (check_if_in_env(*env, variable[i]))
				ret = update_env(*env, variable[i]);
			else
				ret = add_elem_to_env(*env, variable[i]);
		}
		else
		{
			write (2, "Export: Error:", 14);
			write (2, variable[i], ft_strlen(variable[i]));
			write (2, " not a valid identifier\n", 24);
			g_minishexit = 1;
		}
		i++;
	}
	return (ret);
}
