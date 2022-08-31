#include "minishell.h"

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
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

/* Checks if the string passed as parameter matches
 * the name of a special buitin, meaning a builtin that should not
 * be forked when it is the only command in the command line. */
int	is_special_builtin(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!name_len)
		return (0);
	if (ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "exit") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

/* Checks for errors with command in passed segment and
 * prints out corresponding error. */
int	command_error_check(t_command *command)
{
	char		*command_not_found;

	if (!command->cmd_path && command->cmd_array[0]
		&& access(command->cmd_array[0], X_OK == -1))
	{
		command_not_found
			= ft_strjoin(command->cmd_array[0], ": command not found\n");
		ft_printf_fd(2, "%s", command_not_found);
		free(command_not_found);
		command->error_code = 128;
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
