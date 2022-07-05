/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:25:51 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/07/05 19:51:44 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i][0])
		i++;
	return (i);
}

void	env_write(t_env *env, char **envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (env && envp[i][0])
	{
		while (envp[i][j] && envp[i][j - 1] != '=')
			env->name[k++] = envp[i][j++];
		env->name[k] = '\0';
		k = 0;
		while (envp[i][j])
			env->variable[k++] = envp[i][j++];
		env->variable[k] = '\0';
		env = env->next;
		j = 0;
		k = 0;
		i++;
	}
}

t_env	*list_init(t_env *env, int depth)
{
	t_env	*new;

	if (depth <= 0)
		return (NULL);
	new = malloc(sizeof(t_env *));
	if (!new)
		return (NULL);
	new->next = list_init(new->next, depth - 1);
	return (new);
}

t_env	*get_env(char **envp)
{
	int		len;
	t_env	*env;

	len = env_len(envp);
	env = list_init(env, len);
	env_write(env, envp);
	return (env);
}

