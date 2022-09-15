/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command_path_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:33:27 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 11:39:14 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function will split the $PATH environment variable into an array
 * try to find each command in every single folder in the paths provided.
 * If none is found, path variable is set to NULL. If there is a '\' in
 * the command name, the command name will be treated as its path. */
int	assign_command_paths(t_master *master)
{
	char		**paths;
	int			i;

	paths = ft_split(get_path_variable(master->env), ':');
	if (get_path_variable(master->env) && !paths)
		exit(err_msg("malloc fail [assign_command_paths()][1]", 1, master)
			&& free_all(master, 1));
	i = -1;
	while (master->commands[++i])
	{
		if (is_builtin_function(master->commands[i]->cmd_array[0]))
			continue ;
		if (master->commands[i]->cmd_array)
		{
			if (ft_strchr(master->commands[i]->cmd_array[0], '/')
				|| !paths)
				master->commands[i]->cmd_path
					= master->commands[i]->cmd_array[0];
			else if (!get_cmd_path(&master->commands[i]->cmd_path,
					master->commands[i]->cmd_array[0], paths, master))
				return (free_paths(paths), 0);
		}
	}
	free_paths(paths);
	return (1);
}

/* Given a command an array of paths, this function will try to access the
 * command in each path one a a time. If one is found, its path is set.
 * If none is found, the path VARIABLE remains NULL. */
int	get_cmd_path(char **cmd_path, char *command, char **paths, t_master *master)
{
	int		i;
	char	*tmp_path;
	char	*full_path;

	if (command && (ft_strcmp(command, ".") == 0 \
		|| ft_strcmp(command, "..") == 0))
		return (1);
	i = 0;
	while (command && command[0] && paths && paths[i])
	{
		tmp_path = ft_strjoin(paths[i++], "/");
		if (!tmp_path)
			return (err_msg("malloc failed [get_cmd_path()][1]", 1, master));
		full_path = ft_strjoin(tmp_path, command);
		free (tmp_path);
		if (!full_path)
			return (err_msg("malloc failed [get_cmd_path()][2]", 0, master));
		if (access(full_path, X_OK) == 0)
		{
			*cmd_path = full_path;
			break ;
		}
		free(full_path);
	}
	return (1);
}

/* Looks for a variable named PATH in the t_env linked list.
 * If found, the value of that variable is returned. */
char	*get_path_variable(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, "PATH") == 0)
			return (current->variable);
		current = current->next;
	}
	return (NULL);
}

/* Frees a char* array. */
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
		free(paths[i++]);
	free(paths);
}
