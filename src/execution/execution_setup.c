#include "minishell.h"

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
int	prep_execution_resources(t_master *master)
{
	if (!generate_command_structure(master)
		|| !assign_command_paths(master)
		|| !setup_file_descriptors(master)
		|| !setup_process_array(master))
/*		|| !convert_env_to_array(master))*/
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
