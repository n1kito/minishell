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
				exit(free_master(master, 0));
	if (!is_builtin_function(master->commands[i]->cmd_array[0]))
		execve(master->commands[i]->cmd_path,
				master->commands[i]->cmd_array, master->env_array);
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
	while (i < master->cmd_count)
	{
		master->processes[i] = fork();
		if (master->processes[i] == -1)
			return (err_msg("fork failed [exec_loop]", 0, master));
		if (master->processes[i] == 0)
			launch_exec(master, i);
		i++;
	}
	if (!close_pipes(master))
		return(err_msg("could not close pipes", 0, master));
	// TODO export to close_heredocs()
	i = -1;
	while (++i < master->cmd_count)
	{
		if (master->commands[i]->heredoc_fd)
		{
			if (close(master->commands[i]->heredoc_fd) == -1)
				// TODO change this error
				ft_printf_fd(2, "COULD NOT CLOSE FD IN MAIN\n");
			unlink(master->commands[i]->heredoc_path);
		}
	}
	// TODO export to process_waiter()
	i = -1;
	while (++i < master->cmd_count)
		waitpid(master->processes[i], &g_minishexit, 0);
	g_minishexit = WEXITSTATUS(g_minishexit);
	//
	return (1);
}
