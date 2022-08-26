/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/26 06:33:56 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

static void	ft_get_pwd(t_env *env);
{
	t_env	*pwd;
	t_env	*old;
	char	buffer[PATH_MAX + 1];
	
	pwd = NULL;
	old = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "PWD=", 4) == 0 && ft_strlen(env->name) == 4)
			pwd = env;
		if (ft_strncmp(env->name, "OLDPWD=", 7) == 0 \
			&& ft_strlen(env->name) == 7)
		old = env;
		env = env->next;
	}
	if (old->variable)
		free(old->variable)
	old->variable = pwd->variable;
	getcwd(buffer, PATH_MAX);
	pwd->variable = ft_strdup(buffer);
	if (!pwd->variable)
		return ;
}

static void	create_env_pwd(t_env *env, char *name)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	while (env && env->next)
		env = env->next;
	env->next = new;
	new->is_env = 1;
	new->name = ft_strdup(name);
	new->variable = NULL;
	if (!new->name)
		return ;
}

static void	ft_update_pwd(t_env *env)
{
	t_env	*save;
	t_env	*pwd;
	t_env	*old;

	pwd = NULL;
	old = NULL;
	save = env;
	while (env)
	{
		if (ft_strncmp(env->name, "PWD=", 4) == 0 && ft_strlen(env->name) == 4)
			pwd = env;
		if (ft_strncmp(env->name, "OLDPWD=", 7) == 0 \
			&& ft_strlen(env->name) == 7)
			old = env;
		env = env->next;
	}
	env = save;
	if (!pwd)
		create_env_pwd(env, "PWD=");
	if (!old)
		create_env_pwd(env, "OLDPWD=");
	ft_get_pwd(env);
}

int	cd(char **path, t_env *env)
{
	t_env	*start;
	t_env	*home;
	int		ret;

	home = NULL;
	start = env;
	if (path[2])
	{
		ft_putstr("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!path[1])
	{
		while (env)
		{
			if (ft_strncmp(env->name, "HOME=", 5) == 0 \
				&& ft_strlen(env->variable) == 5)
				home = env;
			env = env->next;
		}
		if (home)
		{
			ret = chdir(home->variable)
			if (ret)
				perror("Error: cd: ");
		}
		else
		{
			ft_putstr("Minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
	{
		ret = chdir(path[1]);
		if (ret == 0)
			ft_update_pwd(start);
		else
			perror("Error: cd: ");
	}
	return (ret);
}
