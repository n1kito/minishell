/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/07 15:27:32 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	update_env(t_env *env, char *str)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = NULL;
	while (ft_strncmp(env->name, str, ft_strlen(env->name)) != 0)
		env = env->next;
	while (str[i] && str[i - 1] != '=')
		i++;
	if (str[i])
		tmp = env->variable;
	env->is_env = 1;
	if (str[i] && str[i - 2] && str[i - 2] == '+' && str[i - 1] == '=')
	{
		if (env->variable)
			env->variable = ft_strjoin(env->variable, &str[i]);
		else
			env->variable = ft_strdup(&str[i]);
	}
	else if (str[i] && str[i - 1] && str[i - 1] == '=')
		env->variable = ft_strdup(&str[i]);
	else
		return (free(env->variable), env->variable = NULL, 1);
	if (tmp)
		free(tmp);
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
	ft_strlcpy(new->name, str, i);
	if (str[i])
	{
		new->variable = ft_strdup(&str[i]);
		if (!new->variable)
			return (0);
	}
	env->next = new;
	return (1);
}

static int	check_if_in_env(t_env *env, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] != '=' || str[i] != '+'))
		i++;
	while (env)
	{
		if (ft_strncmp(str, env->name, ft_strlen(env->name)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	arg_is_ok_for_env(char const *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1 && str[0] == '_')
		return (2);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i] && ((str[i] != '=') && (str[i] != '+' && str[i + 1] != '=')))
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

	i = 1;
	ret = 0;
	g_minishexit = 0;
	if (!variable[1])
	{
		print_env_by_alphabetical_order(*env);
		g_minishexit = 0;
		return (1);
	}
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
			write (2, "Export: Error: ", 14);
			write (2, variable[i], ft_strlen(variable[i]));
			write (2, " not a valid identifier\n", 24);
			g_minishexit = 1;
		}
		i++;
	}
	return (ret);
}
