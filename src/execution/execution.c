#include "minishell.h"

void	file_checker(t_master *master, int i)
{
	t_command	*command;

	command = master->commands[i];
}

void	plug_first_command(t_master *master, int i)
{
	file_checker(master, i);
	command_error_check(master, i);
	// add dup2 here
}

void	pipe_plugger(t_master *master, int i)
{
	if (i == 0)
		plug_first_command(master, i);
	else
		plug_nth_command(master, i);
	pipe_and_file_closer(master);
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
	pipe_and_file_closer(master);
	if (!process_waiter(master))
		return (err_msg("waitpid failed", 0, master));
	return (1);
}
