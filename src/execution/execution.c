#include "minishell.h"

void	pipe_plugger(t_master *master, int i)
{
	if (!open_file_descriptors(master, i))
		exit(free_master(master, 1));
	if (!command_is_builtin(master->commands[i]->cmd_array[0]))
		if (!command_error_check(master, i))
			exit(free_master(master, master->commands[i]->error_code));
	if (i == 0)
		plug_first_command(master, i);
	else
		plug_nth_command(master, i);
	pipe_and_file_closer(master);
	if (command_is_builtin(master->command[i]->cmd_array[0]))
		execute_builtin(master);
	else
		execve(master->commands[i]->cmd_path, master->commands[i]->cmd_array, master->env_array);
	exit(free_master(master, 1));
}

int	exec_loop(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->cmd_count)
	{
		master->processes[i] = fork();
		if (master->processes[i] == -1)
			return (err_msg("fork failed [exec_loop]", 1, master));
		if (master->processes[i] == 0)
			pipe_plugger(master, i);
		i++;
	}
	/*
	pipe_and_file_closer(master);
	if (!process_waiter(master))
		return (err_msg("waitpid failed", 0, master));
	*/
	return (1);
}
