/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/05 14:17:30 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function updates OLDPWD if PWD has been unset

static void	ft_update_old(t_env *env, char *buffer)
{
	t_env	*old;

	old = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0 \
				&& ft_strlen(env->name) == 6)
			old = env;
		env = env->next;
	}
	if (old)
	{
		if (old->variable)
			free(old->variable);
		old->variable = NULL;
		if (old->is_env == 1)
			old->is_env = 0;
		else
		{
			old->variable = ft_strdup(buffer);
			old->is_env = 2;
		}
	}
}

//this function updates PWD and also OLDPWD if this one exists

static void	ft_get_pwd(t_env *env)
{
	t_env	*pwd;
	t_env	*old;
	char	buffer[PATH_MAX + 1];

	pwd = NULL;
	old = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", 3) == 0 && ft_strlen(env->name) == 3)
			pwd = env;
		if (ft_strncmp(env->name, "OLDPWD", 6) == 0 \
				&& ft_strlen(env->name) == 6)
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

//This function checks if PWD exists
//if it does it the environment will be updated in a specific way using pwd
//if not, only OLDPWD will ne updated using the buffer

static void	ft_update_pwd(t_env *env, char *buffer)
{
	t_env	*save;
	t_env	*pwd;

	pwd = NULL;
	save = env;
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", 3) == 0 && ft_strlen(env->name) == 3)
			pwd = env;
		env = env->next;
	}
	if (pwd)
		ft_get_pwd(save);
	if (!pwd)
		ft_update_old(save, buffer);
}

//This function is called if no ath is given to cd
//it will look for the home variable in the environment
//if no HOME is found it will return an Error
//otherwise it will use chdir with the path found in HOME

static int	find_home(t_env *env)
{
	t_env	*home;
	int		ret;

	home = NULL;
	while (env)
	{
		if (ft_strncmp(env->name, "HOME", 4) == 0 \
				&& ft_strlen(env->variable) == 4)
			home = env;
		env = env->next;
	}
	if (home)
	{
		ret = chdir(home->variable);
		if (ret)
			perror("Error: cd: ");
		return (0);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
}

//This function takes a path as well as an env
//It parses the arguments to see if there is any Errorif no arguments are given,
//it will go to the home dir set in the env
//Otherwise it will give the path to the chdir function
//It will then update the PWD and OLDPWD accordingly
//in case of an error, it returns a 1 and a 0 in case of success

int	ft_cd(char **path, t_env *env)
{
	t_env	*start;
	int		ret;
	char	buffer[PATH_MAX + 1];

	start = env;
	ret = 0;
	if (getcwd(buffer, PATH_MAX))
	{
		if (path[2])
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			g_minishexit = 1;
		}
		if (!path[1])
			ret = find_home(env);
		else
			ret = chdir(path[1]);
		if (ret == 0)
			ft_update_pwd(start, buffer);
		if (ret != 0)
			perror("Error: cd: ");
		ret = g_minishexit;
		if (g_minishexit)
			return (0);
		return (1);
	}
	else
	{
		perror("Error: cd: ");
		g_minishexit = 1;
		return (0);
	}
}
