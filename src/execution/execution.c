#include "minishell.h"

/* Opens all necessary files and plugs pipes accordingly.
 * Builtin functions are launched without execve(). */
void	launch_exec(t_master *master, int i)
{
	int	input_redirection;
	int	output_redirection;

	if (!open_file_descriptors(master, i))
		exit(free_master(master, 1));
	if (!is_builtin_function(master->commands[i]->cmd_array[0]))
		if (!command_error_check(master->commands[i]))
			exit(free_master(master, master->commands[i]->error_code));
	input_redirection = last_input_fd(master, i);
	output_redirection = last_output_fd(master, i);
	if (i == 0)
		plug_first_cmd(master, i, input_redirection, output_redirection);
	else if (i == master->cmd_count - 1)
		plug_last_cmd(master, i, input_redirection, output_redirection);
	else
		plug_middle_cmd(master, i, input_redirection, output_redirection);
	close_pipes_and_files(master, i);
	if (!master->commands[i]->cmd_array[0]
		|| (is_builtin_function(master->commands[i]->cmd_array[0])
			&& !run_builtin(master, i)))
		exit(clean_env(&master->env, 0) && free_master(master, 0));
	if (!is_builtin_function(master->commands[i]->cmd_array[0])
		&& env_for_exe(master))
		execve(master->commands[i]->cmd_path,
			master->commands[i]->cmd_array, master->env_for_exec);
	exit(clean_env(&master->env, 1) && free_master(master, 1));
}

/* Loops through the command segments and creates a fork for each,
 * then it launched execution, waits for it to end and cleans everything up. */
//TODO add the master_reset() function at the end of this one.
int	exec_loop(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->cmd_count)
	{
		master->processes[i] = fork();
		if (master->processes[i] == -1)
			return (err_msg("fork failed [exec_loop]", 0, master));
		if (master->processes[i] == 0)
			launch_exec(master, i);
		i++;
	}
	if (!close_pipes(master)
		|| !close_heredocs(master)
		|| !process_waiter(master))
		return (0);
	return (1);
}
