#include "minishell.h"

// TODO move somewhere else
/* Checks the current tokens for a heredoc token. */
int	heredoc_found(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->token_type == HERE_DOC)
			return (1);
		current = current->next;
	}
	return (0);
}

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
void	prep_execution_resources(t_master *master)
{
	generate_command_structure(master);
	if (!assign_command_paths(master))
		exit(free_all(master, 1));
	allocate_file_descriptors(master);
	setup_heredocs(master);
	if (heredoc_found(master) && g_minishexit == 130) // did we CTRL + C out of heredocs ?
		return ;
	setup_process_array(master);
	setup_pipes(master);
	return ;
}

/* Allocates memory for the int array used to
 * store PIDs. */
void	setup_process_array(t_master *master)
{
	int	command_count;

	command_count = master->cmd_count;
	master->processes = malloc(sizeof(int) * command_count);
	if (!master->processes)
		exit(err_msg("malloc failed [setup_process_array]", 1, master)
			&& free_all(master, 1));
}

/* If pipes are needed, function allocates and initialises the
 * necessary pipes to execute the command line. There are cmd_count - 1
 * pipes. */
void	setup_pipes(t_master *master)
{
	int	i;

	if (master->cmd_count < 2)
		return ;
	master->pipes = malloc(sizeof(int *) * (master->cmd_count - 1));
	if (!master->pipes)
		exit(err_msg("malloc failed [setup_pipes()][1]", 1, master)
			&& free_all(master, 1));
	i = master->cmd_count - 1;
	while (--i >= 0)
		master->pipes[i] = NULL;
	while (++i < master->cmd_count - 1)
	{
		master->pipes[i] = malloc(sizeof(int) * 2);
		if (!master->pipes[i])
			exit(err_msg("malloc failed [setup_pipes()][2]", 1, master)
				&& free_all(master, 1));
	}
	while (--i >= 0)
	{
		master->pipes[i][0] = -1;
		master->pipes[i][1] = -1;
	}
	while (++i < master->cmd_count - 1)
		if (pipe(master->pipes[i]) == -1)
			exit(err_msg("pipe failed [setup_pipes()]", 1, master)
				&& free_all(master, 1));
}
