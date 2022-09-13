/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/13 17:03:22 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function updates OLDPWD if PWD has been unset

void	check_malloc_in_builtin(t_master *master, t_env *env)
{
	int command;

	command = master->cmd_count;
	if (!env || !env->name || !env->variable)
	{
		write(2, "Minishell failure: malloc error in builtin cd\n", 47);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
	if (env->is_env && !env->variable)
	{
		write(2, "Minishell failure: malloc error in builtin cd\n", 47);
		free_all(master, g_minishexit);
		if (command > 1)
			exit(42);
		exit(1);
	}
}

static void	ft_update_old(t_master *master, char *buffer)
{
	t_env	*old;
	t_env	*env;

	env = master->env;
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
		if (old->is_env == 1)
			old->is_env = 0;
		else
		{
			old->is_env = 2;
			old->variable = ft_strdup(buffer);
			check_malloc_in_builtin(master, old);
		}
	}
}

//this function updates PWD and also OLDPWD if this one exists

static void	ft_get_pwd(t_master *master)
{
	t_env	*env;
	t_env	*pwd;
	t_env	*old;
	char	buffer[PATH_MAX + 1];

	env = master->env;
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
	if (old && old->variable)
		free(old->variable);
	if (old)
		old->variable = pwd->variable;
	getcwd(buffer, PATH_MAX);
	pwd->variable = ft_strdup(buffer);
	check_malloc_in_builtin(master, pwd);
}

//This function checks if PWD exists
//if it does it the environment will be updated in a specific way using pwd
//if not, only OLDPWD will ne updated using the buffer

static void	ft_update_pwd(t_master *master, char *buffer)
{
	t_env	*save;
	t_env	*pwd;

	pwd = NULL;
	g_minishexit = 0;
	save = master->env;
	while (save)
	{
		if (ft_strncmp(save->name, "PWD", 3) == 0 && ft_strlen(save->name) == 3)
			pwd = save;
		save = save->next;
	}
	if (pwd)
		ft_get_pwd(master);
	if (!pwd)
		ft_update_old(master, buffer);
}

//This function is called if no ath is given to cd
//it will look for the home variable in the environment
//if no HOME is found it will return an Error
//otherwise it will use chdir with the path found in HOME

static void	find_home(t_env *env)
{
	int		ret;

	ret = 0;
	while (env)
	{
		if (ft_strncmp("HOME", env->name, 4) == 0 && ft_strlen(env->name) == 4)
		{
			if (env->variable && env->variable[0])
			{
				ret = chdir(env->variable);
				break;
			}
		}
		env = env->next;
	}
	if (ret == -1)
		perror("Error: cd: ");
	if (!env)
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
}

//This function takes a path as well as an env
//It parses the arguments to see if there is any Errorif no arguments are given,
//it will go to the home dir set in the env
//Otherwise it will give the path to the chdir function
//It will then update the PWD and OLDPWD accordingly
//in case of an error, it returns a 1 and a 0 in case of success

void	ft_cd(t_master *master, char **path)
{
	int		ret;
	char	buffer[PATH_MAX + 1];

	g_minishexit = 1;
	ret = 0;
	if (getcwd(buffer, PATH_MAX))
	{
		if (!path[1])
			find_home(master->env);
		else if (path[2])
		{
			ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
			return ;
		}
		else
			ret = chdir(path[1]);
		if (ret == 0)
			ft_update_pwd(master, buffer);
		if (ret == -1)
		{
			ft_printf_fd(2, "Error: cd: \'%s\': ", path[1]);
			perror("");
		}
	}
	else
		perror("Error: cd: ");
}
