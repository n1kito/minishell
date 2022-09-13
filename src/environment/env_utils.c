/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:59:03 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/13 18:01:39 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_env(t_env **env, int return_code)
{
	t_env	*tmp;
	t_env	*lst;

	tmp = NULL;
	lst = *env;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->variable)
			free(tmp->variable);
		if (tmp)
			free(tmp);
	}
	*env = NULL;
	return (return_code);
}

int	is_in_env(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*get_env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}
