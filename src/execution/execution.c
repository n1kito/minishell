#include "minishell.h"

int	last_input_fd(t_master *master, int i)
{
	t_tokens	*current;
	int			fd_index;

	current = go_to_nth_segment(i, master->tokens);
	fd_index = count_files_in_segment(master, i) - 1;
	while (current && current->next
			&& current->next->token_type != PIPE_TOKEN)
		current = current->next;
	while (current)
	{
		if (current->token_type == HERE_DOC)
			return (master->commands[i]->heredoc_fd);
		if (current->token_type == REDIRECT_FROM)
			return (master->commands[i]->fds[fd_index]);
		if (current->token_type == REDIRECT_TO
			|| current->token_type == APPEND)
			fd_index--;
		if (!current->previous || current->previous->token_type == PIPE_TOKEN)
			break ;
		else
			current = current->previous;
	}
	return (0);
}

int	last_output_fd(t_master *master, int i)
{
	t_tokens	*current;
	int			fd_index;
	
	current = go_to_nth_segment(i, master->tokens);
	fd_index = master->commands[i]->redirections_count - 1;
	while (current && current->next
			&& current->next->token_type != PIPE_TOKEN)
		current = current->next;
	while (current)
	{
		if (current->token_type == REDIRECT_TO
			|| current->token_type == APPEND)
			return (master->commands[i]->fds[fd_index]);
		if (current->token_type == REDIRECT_FROM)
			fd_index--;
		if (!current->previous || current->previous->token_type == PIPE_TOKEN)
			break ;
		else
			current = current->previous;
	}
	return (0);
}

void	launch_exec(t_master *master, int i)
{
	int	input_redirection;
	int	output_redirection;

	if (!open_file_descriptors(master, i))
		exit(free_master(master, 1));
	if (!is_builtin_function(master->commands[i]->cmd_array[0]))
		if (!command_error_check(master->commands[i]))
			exit(free_master(master, master->commands[i]->error_code));
	// redirections
	input_redirection = last_input_fd(master, i);
	output_redirection = last_output_fd(master, i);
	if (input_redirection)
	{
		if (dup2(input_redirection, STDIN_FILENO) == -1)
			exit(err_msg("dup2 failed", i, master) && free_master(master, 1));
	}
	else
	{
		if (i)
			if (dup2(master->pipe[0], STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", i, master) && free_master(master, 1));
	}
	if (output_redirection)
	{
		if (dup2(output_redirection, STDOUT_FILENO) == -1)
			exit(err_msg("dup2 failed", i, master) && free_master(master, 1));
	}
	else
	{
		if (i < master->cmd_count - 1)
			if (dup2(master->pipe[1], STDOUT_FILENO) == -1)
				exit(err_msg("dup2 failed", i, master) && free_master(master, 1));
	}
	// end of redirections
	close(master->pipe[0]);
	close(master->pipe[1]);
	/*
	int x = 0;
	while (x < count_files_in_segment(master, i))
		close(master->commands[i]->fds[x++]);
	*/
	execve(master->commands[i]->cmd_path, master->commands[i]->cmd_array, master->env_array);
	/*
	if (i == 0)
		plug_first_command(master, i);
	else
		plug_nth_command(master, i);
	pipe_and_file_closer(master);
	if (is_builtin_function(master->command[i]->cmd_array[0]))
		execute_builtin(master);
	else
		execve(master->commands[i]->cmd_path,
			master->commands[i]->cmd_array, master->env_array);
		*/
	exit(free_master(master, 1));
}

//TODO implement builtins here. If there is only one command count
// and it is a special builtin, the files are still created etc
// but OUTSIDE of a fork. Therefore the builtin is only executed
// if there are no issues with the files. */
int	exec_loop(t_master *master)
{
	int	i;

	i = 0;
	// TODO: should I move this pipe init somewhere else ?
	if (pipe(master->pipe) == -1)
		return (err_msg("pipe failed", 1, master));
	//if (master->cmd_count == 1
	//	&& is_special_builtin(master->commands[0]->cmd_array[0]))
		//launch_special_builting(master);
	//else
	//{
		while (i < master->cmd_count)
		{
			master->processes[i] = fork();
			if (master->processes[i] == -1)
				return (err_msg("fork failed [exec_loop]", 1, master));
			if (master->processes[i] == 0)
				launch_exec(master, i);
			i++;
		}
		/*
		pipe_and_file_closer(master);
		if (!process_waiter(master))
			return (err_msg("waitpid failed", 0, master));
		*/
	//}
	return (1);
}
