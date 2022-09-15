#include "minishell.h"

void	close_pipes_and_files(t_master *master, int i)
{
	close_pipes(master);
	close_files(master, i);
}

void	close_pipes(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->cmd_count - 1)
	{
		if (close(master->pipes[i][0]) == -1
			|| close(master->pipes[i][1]) == -1)
			exit(err_msg("could not close pipes [close_pipes()]",
					1, master) && free_all(master, 1));
		i++;
	}
	if (master->tmp_stdin >= 0)
		if (close(master->tmp_stdin) == -1)
			exit(err_msg("could not close tmp_stdin [close_pipes()]",
					1, master) && free_all(master, 1));
	if (master->tmp_stdout >= 0)
		if (close(master->tmp_stdout) == -1)
			exit(err_msg("could not close tmp_stdout [close_pipes()]",
					1, master) && free_all(master, 1));
}

void	close_files(t_master *master, int i)
{
	int	j;

	if (master->commands[i]->heredoc_path)
		if (close(master->commands[i]->heredoc_fd) == -1)
			exit(err_msg("heredoc close() failed [close_files()][1]",
				1, master) && free_all(master, 1));
	if (master->commands[i]->redirections_count == 0)
		return ;
	j = 0;
	while (j < master->commands[i]->redirections_count)
	{
		if (master->commands[i]->fds[j])
			if (close(master->commands[i]->fds[j]) == -1)
				exit(err_msg("close() failed [close_files()][2]",
						1, master) && free_all(master, 1));
		j++;
	}
}

/* Checks if the string passed as parameter matches
 * the name of one of the builtins. */
int	is_builtin_function(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!name_len)
		return (0);
	if (ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "exit") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

/* Checks for errors with command in passed segment and
 * prints out corresponding error. */
// TODO protect stdjoin
int	command_error_check(t_command *command, t_master *master)
{
	int			is_directory;
	char		*error_message;

	is_directory = 0;
	if (command->cmd_array && command->cmd_array[0])
		is_directory = open(command->cmd_array[0], O_DIRECTORY);
	if (!command->cmd_path
		&& ((command->cmd_array[0] && access(command->cmd_array[0], X_OK) == -1)
			|| !command->cmd_array
			|| ft_strcmp(command->cmd_array[0], ".") == 0
			|| ft_strcmp(command->cmd_array[0], "..") == 0
			|| (command->cmd_array && is_directory && !ft_strchr(command->cmd_array[0], '/'))))
	{
		if (is_directory >= 0)
			close(is_directory);
		error_message
			= ft_strjoin(command->cmd_array[0], ": command not found\n");
		if (!error_message)
		{
			err_msg("malloc fail [command_error_check()][1]", 0, master);
			exit(free_all(master, 42));
		}
		ft_printf_fd(2, "%s", error_message);
		free(error_message);
		command->error_code = 127;
	}
	else if (is_directory != -1)
	{
		close(is_directory);
		error_message = ft_strjoin(command->cmd_array[0], ": Is a directory\n");
		if (!error_message)
		{
			err_msg("malloc fail [command_error_check()][2]", 0, master);
			exit(free_all(master, 42));
		}
		ft_printf_fd(2, "%s", error_message);
		free(error_message);
		command->error_code = 126;
	}
	else if (command->cmd_path && access(command->cmd_path, F_OK) == -1)
	{
		perror(command->cmd_path);
		command->error_code = 127;
	}
	else if (command->cmd_path && access(command->cmd_path, X_OK) == -1)
	{
		perror(command->cmd_path);
		command->error_code = 126;
	}
	if (command->error_code)
		return (0);
	return (1);
}
