/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:57:14 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 17:14:11 by vrigaudy         ###   ########.fr       */
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

static void	update_env(t_master *master, t_env *env, char *str)
{
	if (str[0] == '+' && str[1] == '=')
		env->variable = update_env_plus(env->variable, str + 2);
	if (str[0] == '=')
	{
		if (env->variable)
			free(env->variable);
		if (*(str + 1))
			env->variable = ft_strdup(str + 1);
		else
			env->variable = ft_strdup("");
	}
	if (!env || !env->variable || !env->name)
	{
		ft_putstr_fd("Minishell failure: malloc error in builtin ", 2);
		write(2, "export", 6);
		write(2, "\n", 1);
		if (master->cmd_count > 1)
			exit(42);
		exit(1);
	}
}

static void	add_elem_to_env(t_master *master, t_env *save, char *str)
{
	int		i;
	t_env	*new;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	new = ft_calloc(sizeof(t_env), 1);
	check_malloc_in_builtin(master, save, "export");
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
	check_malloc_in_builtin(master, save, "export");
	save->next = new;
}

static void	check_if_in_env(t_master *master, t_env *save, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	while (save)
	{
		if (ft_strncmp(str, save->name, ft_strlen(save->name)) == 0 \
				&& ft_strlen(save->name) == i)
		{
			update_env(master, save, &str[i]);
			return ;
		}
		if (!save->next)
			break;
		save = save->next;
	}
	if (!save->next)
	{
		while (str[i] && str[i] != '=')
			i++;
		add_elem_to_env(master, save, str);
	}
}

int	arg_is_ok_for_env(char const *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (2);
	if ((str[0] == '_' && (str[1] == '+' || str[1] == '=')))
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
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

void	ft_export(t_master *master, char **variable)
{
	int		i;
	t_env	*save;

	save = master->env;
	i = 1;
	g_minishexit = 0;
	if (!variable[1])
		print_env_by_alphabetical_order(master->env);
	while (variable[i])
	{
		if (arg_is_ok_for_env(variable[i]) == 0)
			check_if_in_env(master, save, variable[i]);
		else if (arg_is_ok_for_env(variable[i]) == 1)
		{
			write (2, "Export: Error: '", 16);
			write (2, variable[i], ft_strlen(variable[i]));
			write (2, "' not a valid identifier\n", 25);
			g_minishexit = 1;
		}
		i++;
	}
}
