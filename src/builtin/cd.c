/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/31 01:27:21 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>
#include <limits.h>

static void	update_both_pwd(t_env *env)
{
	t_env	*old;
	t_env	*pwd;
	char	buffer[PATH_MAX + 1];

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
		free(old->variable);
	old->variable = pwd->variable;
	getcwd(buffer, PATH_MAX);
	pwd->variable = malloc(sizeof(char) * ft_strlen(buffer) + 1);
	ft_strlcpy(pwd->variable, buffer, ft_strlen(buffer));
}

static t_env	*add_node(t_env *env, char *str)
{
	t_env	*temp;
	t_env	*new;

	temp = env;
	while (temp->next)
		temp = temp->next;
	new = malloc(sizeof(t_env *));
	if (!new)
		return (NULL);
	new->name = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new->name)
		return (NULL);
	ft_strlcpy(new->name, str, ft_strlen(str));
	new->variable = NULL;
	temp->next = new;
	return (env);
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
		env = add_node(env, "PWD=");
	if (!old)
		env = add_node(env, "OLDPWD=");
	update_both_pwd(env);
}

int	cd(char *path, t_env *env)
{
	int		ret;

	if (!path)
	{
		while (ft_strncmp(env->name, "HOME=", 5) != 0)
			env = env->next;
		if (!env || !env->variable)
			ft_putstr_fd("cd: HOME not set\n", 2);
		ret = chdir(env->variable);
	}
	else
		ret = chdir(path);
	if (ret == 0)
		ft_update_pwd(env);
	return (ret);
}
