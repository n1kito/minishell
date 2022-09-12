/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 10:37:19 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	*update_env_plus(char *initial_value, char *added_value)
{
	char	*tmp;

	tmp = NULL;
	if (!added_value || !added_value[0])
		return (initial_value);
	if (!initial_value)
		initial_value = ft_strdup(added_value);
	else
	{
		tmp = initial_value;
		initial_value = ft_strjoin(initial_value, added_value);
		free(tmp);
	}
	if (!initial_value)
		return (NULL);
	return (initial_value);
}

static int	update_env(t_env *env, char *str)
{
	if (str[0] == '+' && str[1] == '=')
	{
		env->variable = update_env_plus(env->variable, str + 2);
		if (!env->variable)
			return (0);
	}
	if (str[0] == '=')
	{
		if (env->variable)
			free(env->variable);
		if (*(str + 1))
			env->variable = ft_strdup(str + 1);
		else
			env->variable = ft_strdup("");
		if (!env->variable)
			return (0);
	}
	return (1);
}

static int	add_elem_to_env(t_env *env, char *str)
{
	int		i;
	t_env	*new;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (0);
	if (str[i] == '=' || str[i] == '+')
		new->is_env = 1;
	new->name = malloc(sizeof(char) * (i + 1));
	if (new->name)
		ft_strlcpy(new->name, str, i + 1);
	if (str[i] && str[i] == '+')
		i++;
	if (str[i + 1])
		new->variable = ft_strdup(&str[i + 1]);
	else
		new->variable = ft_strdup("");
	if (!new->name || !new->variable)
		return (free(new), 0);
	env->next = new;
	return (1);
}

static int	check_if_in_env(t_env *env, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	while (env)
	{
		if (ft_strncmp(str, env->name, ft_strlen(env->name)) == 0 \
				&& ft_strlen(env->name) == i)
			return (update_env(env, &str[i]));
		if (!env->next)
			break;
		env = env->next;
	}
	while (str[i] && str[i] != '=')
		i++;
	return(add_elem_to_env(env, str));
}

int	arg_is_ok_for_env(char const *str)
{
	int	i;

	i = 0;
	if (!arg[0])
		return (2);
	if (str[0] == '_' && (str[1] == '+' || str[1] == '='))
		return (2);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (0);
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
		return (1);
	}
	while (variable[i])
	{
		if (arg_is_ok_for_env(variable[i]) == 0)
			ret = (check_if_in_env(*env, variable[i]));
		else if (arg_is_ok_for_env(variable[i]) == 2)
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
