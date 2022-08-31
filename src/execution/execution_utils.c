#include "minishell.h"

int	is_builtin_function(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!name_len)
		return (0);
	if (ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "pwd") == 0 // not sure this one but probably
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}

int	command_error_check(t_master *master, int i)
{
	t_command	*command;

	command = master->commands[i];
	if (!command->cmd_path)
	{
		ft_printf_fd(2, "%s: command not found\n", command->cmd_array[0]);
		command->error_code = 127;	
		return (0);
	}
	else if (access(command->cmd_path, F_OK) == -1)
	{
		ft_printf_fd(2, "%s: No such file or directory\n", command->cmd_path);
		command->error_code = 127;
		return (0);
	}
	else if (access(command->cmd_path, X_OK) == -1)
	{
		ft_printf_fd(2, "%s: Permission denied\n", command->cmd_path);
		command->error_code = 126;
		return (0);
	}
	return (1);
}
