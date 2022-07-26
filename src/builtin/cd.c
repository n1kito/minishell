/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:21:35 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/26 03:10:32 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>



int	cd(char *path, t_env *env)
{
	int		ret;
	char	*new_pwd;

	if (!path)
	{
		while (ft_strncmp(env->name, "HOME=", 5) != 0)
			env = env->next;
		if (!env)
			printf("cd: HOME not set\n");
		ret = chdir(env->variable);
	}
	else if (strncmp(path, "~", 1) == 0 && ft_strlen(path) == 1)
	{

	}
	else
		ret = chdir(path);
	if (!ret)
		ft_update_pwd(env);
	return (ret);
}
