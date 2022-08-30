#include "minishell.h"

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
