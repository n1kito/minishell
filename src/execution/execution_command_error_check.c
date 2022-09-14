/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command_error_check.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:25:52 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/14 22:05:17 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_command(t_master *master, t_command *com, int dir, int ret)
{
	char	*error_message;

	if (dir >= 0)
		close(dir);
	if (ret == 127)
		error_message = ft_strjoin(com->cmd_array[0], ": command not found\n");
	else
		error_message = ft_strjoin(com->cmd_array[0], ": Is a directory\n");
	if (!error_message)
		exit(err_msg("malloc fail [command_error_check()]", 0, master) \
			&& (free_all(master, 42)));
	ft_printf_fd(2, "%s", error_message);
	free(error_message);
	return (ret);
}

/* Checks for errors with command in passed segment and
 * prints out corresponding error. */
// TODO protect stdjoin
int	command_error_check(t_command *command, t_master *master)
{
	int	is_directory;

	is_directory = 0;
	if (command->cmd_array && command->cmd_array[0])
		is_directory = open(command->cmd_array[0], O_DIRECTORY);
	if (!command->cmd_path && ((command->cmd_array[0] \
		&& access(command->cmd_array[0], X_OK) == -1) || !command->cmd_array \
		|| ft_strcmp(command->cmd_array[0], ".") == 0 \
		|| ft_strcmp(command->cmd_array[0], "..") == 0 \
		|| (command->cmd_array && is_directory \
		&& !ft_strchr(command->cmd_array[0], '/'))))
		command->error_code = error_command(master, command, is_directory, 127);
	else if (is_directory != -1)
		command->error_code = error_command(master, command, is_directory, 126);
	else if (command->cmd_path && access(command->cmd_path, F_OK) == -1)
		command->error_code = 127;
	else if (command->cmd_path && access(command->cmd_path, X_OK) == -1)
		command->error_code = 126;
	if ((command->cmd_path && access(command->cmd_path, F_OK) == -1) \
		|| (command->cmd_path && access(command->cmd_path, X_OK) == -1))
		perror(command->cmd_path);
	if (command->error_code)
		return (0);
	return (1);
}
