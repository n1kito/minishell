/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:33:40 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/12 16:36:28 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	check_match(char *name, char *arg)
//{
//	if (ft_strncmp(name, arg, ft_strlen(arg)) == 0)
//	{
//		if (ft_strlen(name) == ft_strlen(arg))
//			return (1);
//	}
//	return (0);
//}

static int	ft_print_error(char *variable)
{
	write (2, "Unset: Error: \"", 15);
	write (2, variable, ft_strlen(variable));
	write (2, "\" not a valid identifier\n", 26);
	return (1);
}

//static t_env	*unset_middle(t_env *env, t_env *start)
//{
//	while (start && start->next != env)
//		start = start->next;
//	if (env->next)
//		start->next = env->next;
//	else
//		start->next = NULL;
//	if (env->name)
//	{
//		free(env->name);
//		env->name = NULL;
//	}
//	if (env->variable)
//	{
//		free(env->variable);
//		env->variable = NULL;
//	}
//	env->is_env = 0;
//	if (env)
//	{
//		free(env);
//		env = NULL;
//	}
//	return (start);
//}
//
//static t_env	*ft_swap(t_env *env)
//{
//	t_env	*tmp;
//	t_env	*start;
//
//	start = env->next;
//	tmp = env;
//	while (env && env->next)
//		env = env->next;
//	env->next = tmp;
//	tmp->next = NULL;
//	return (start);
//}

/* Search for variable name in env.
 * Returns variable value if found, NULL if not. */
t_env	*search_env2(t_env *env, char *name, int name_len)
{
	t_env	*current;
	int		i;

	current = env;
	while (current)
	{
		i = 0;
		while (current->name[i] == name[i] && i < name_len)
			i++;
		if (i == name_len && current->name[i] == '\0')
			return (current);
		else
			current = current->next;
	}
	return (NULL);
}

t_env	*get_previous_token(t_env *env, t_env *token)
{
	while (env->next && env->next->next != token)
		env = env->next;
	return (env);
}

void	unset_env_node(t_env **env, t_env *token)
{
	if (lstlen(*env) == 1 || token->next == NULL)
	{
		free(token->name);
		free(token->variable);
		free(token);
	}
	else if (token == *env)
	{
		*env = token->next;
		free(token->name);
		free(token->variable);
		free(token);
	}
	else
	{
		get_previous_token(*env, token)->next = token->next;
		free(token->name);
		free(token->variable);
		free(token);
	}
}

void	ft_unset(t_env **env, char **arg)
{
	int		i;
	t_env	*start;

	i = 1;
	start = *env;
	g_minishexit = 0;
	while (arg[i] && *env)
	{
		if (arg_is_ok_for_env(arg[i]) == 0 && *env)
		{
			unset_env_node(env, search_env2(*env, arg[i], ft_strlen(arg[i])));
		}
		else if (arg_is_ok_for_env(arg[i]))
			g_minishexit = ft_print_error(arg[i]);
		i++;
		*env = start;
	}
}
