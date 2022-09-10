#include "minishell.h"

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
int	prep_execution_resources(t_master *master)
{
	if (!generate_command_structure(master)
		|| !assign_command_paths(master)
		|| !setup_file_descriptors(master))
		return (0);
	if (g_minishexit == 130) // did we CTRL + C out of heredocs ?
		return (1);
	if (!setup_process_array(master)
		|| !setup_pipes(master))
/*		|| !convert_env_to_array(master))*/ // this is done in exec actually
		return (0);
	return (1);
}

/* Allocates memory for the int array used to
 * store PIDs. */
int	setup_process_array(t_master *master)
{
	int	command_count;

	command_count = master->cmd_count;
	master->processes = malloc(sizeof(int) * command_count);
	if (!master->processes)
		return (err_msg("malloc failed [setup_process_array]", 0, master));
	return (1);
}

/* If pipes are needed, function allocates and initialises the
 * necessary pipes to execute the command line. There are cmd_count - 1
 * pipes. */
int	setup_pipes(t_master *master)
{
	int	i;

	if (master->cmd_count < 2)
		return (1);
	master->pipes = malloc(sizeof(int *) * (master->cmd_count - 1));
	if (!master->pipes)
		return (err_msg("malloc failed [setup_pipes()][1]", 0, master));
	i = master->cmd_count - 1;
	while (--i >= 0)
		master->pipes[i] = NULL;
	while (++i < master->cmd_count - 1)
	{
		master->pipes[i] = malloc(sizeof(int) * 2);
		if (!master->pipes[i])
			return (err_msg("malloc failed [setup_pipes()][2]", 0, master));
	}
	while (--i >= 0)
	{
		master->pipes[i][0] = -1;
		master->pipes[i][1] = -1;
	}
	while (++i < master->cmd_count - 1)
		if (pipe(master->pipes[i]) == -1)
			return (err_msg("pipe failed [setup_pipes()]", 0, master));
	return (1);
}
