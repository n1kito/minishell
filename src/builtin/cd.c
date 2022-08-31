/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/31 22:10:40 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

static void	ft_update_old(t_env *env, char *buffer)
{
	t_env	*old;

	old = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "OLDPWD=", 7) == 0 \
			&& ft_strlen(env->name) == 7)
			old = env;
		env = env->next;
	}
	if (old)
	{
		if (old->variable)
			free(old->variable);
		old->variable = ft_strdup(buffer);
	}
}

static void	ft_get_pwd(t_env *env)
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
	if (old)
	{
		if (old->variable)
			free(old->variable);
		old->variable = pwd->variable;
	}
	getcwd(buffer, PATH_MAX);
	pwd->variable = ft_strdup(buffer);
}

static void	ft_update_pwd(t_env *env, char *buffer)
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
	if (pwd)
		ft_get_pwd(env);
	if (!pwd)
		ft_update_old(env, buffer);
}

static int	find_home(t_env *env)
{
	t_env	*home;
	int		ret;

	home = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "HOME=", 5) == 0 \
			&& ft_strlen(env->variable) == 5)
			home = env;
		env = env->next;
	}
	if (home)
	{
		ret = chdir(home->variable);
		if (ret)
			perror("Error: cd: ");
	}
	else
	{
		ft_putstr("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
}

int	cd(char **path, t_env *env)
{
	t_env	*start;
	t_env	*home;
	int		ret;
	char	buffer[MAX_PATH + 1];

	home = NULL;
	start = env;
	getcwd(buffer, PATH_MAX);
	if (path[2])
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!path[1])
		ret = find_home(env);
	else
		ret = chdir(path[1]);
	if (ret == 0)
		ft_update_pwd(start, buffer);
	if (ret != 0)
		perror("Error: cd: ");
	return (ret);
}
