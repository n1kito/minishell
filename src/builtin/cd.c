/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/24 20:44:23 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
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
	pwd->variable = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!pwd->variable)
		return ;
	ft_strlcpy(new->name, name, ft_strlen(name));
}

static void	create_env_pwd(t_env *env, char *name)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	while (env && env->next)
		env = env->next;
	env->next = new;
	new->is_env = 1;
	new->name = malloc(sizeof(char) * (ft_strlen(name) + 1));
	if (!new->name)
		return ;
	ft_strlcpy(new->name, name, ft_strlen(name));
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

int	cd(char *path, t_env *env)
{
	int		ret;

	ret = chdir(path);
	if (ret == 0)
		ft_update_pwd(env);
	else
		perror("Error: cd: ");
	return (ret);
}
