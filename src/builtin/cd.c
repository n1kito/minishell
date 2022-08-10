/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/08/10 19:48:15 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <unistd.h>
#include <limits.h>

static void	update_oldpwd(t_env *env, char *oldpwd)
{
	t_env	*old;

	while (env)
	{
		if (ft_strncmp(env->name, "OLDPWD=", 7) == 0 \
			&& ft_strlen(env->name) == 7)
			old = env;
		env = env->next;
	}
	if (old->variable)
		free(old->variable);
	old->variable = malloc(sizeof(char) * ft_strlen(oldpwd) + 1);
	ft_strlcpy(old->variable, oldpwd, ft_strlen(oldpwd));
}

static void	update_pwd(t_env *env)
{
	t_env	*pwd;
	char	buffer[PATH_MAX + 1];

	while (env)
	{
		if (ft_strncmp(env->name, "PWD=", 4) == 0 && ft_strlen(env->name) == 4)
			pwd = env;
		env = env->next;
	}
	if (pwd->variable)
		free(pwd->variable);
	getcwd(buffer, PATH_MAX);
	pwd->variable = malloc(sizeof(char) * ft_strlen(buffer) + 1);
	ft_strlcpy(pwd->variable, buffer, ft_strlen(buffer));
}

static void	ft_update_pwd(t_env *env, char *oldpwd)
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
	if (pwd)
		update_pwd(env);
	if (old)
		update_oldpwd(env, oldpwd);
}

int	cd(char *path, t_env *env)
{
	int		ret;
	char	buffer[PATH_MAX + 1];

	ret = chdir(path);
	if (ret == 0)
		ft_update_pwd(env, buffer);
	return (ret);
}
