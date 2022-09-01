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
	if (i == 0)// handle first command
	{
		if (input_redirection)
		{
			if (dup2(input_redirection, STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close(input_redirection);
		}
		if (output_redirection)
		{
			if (dup2(output_redirection, STDOUT_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close(output_redirection);
		}
		else
		{
			if (master->cmd_count > 1)
			{
				if (dup2(master->pipes[i][1], STDOUT_FILENO) == -1)	
					exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
				//close(master->pipe[1]);
			}
		}
		//close(master->pipe[0]);
	}
	else if (i == master->cmd_count - 1) // handle last command
	{
		if (input_redirection)
		{
			if (dup2(input_redirection, STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close (input_redirection);
		}
		else
		{
			if (dup2(master->pipes[i - 1][0], STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close (master->pipe[0]);
		}
		if (output_redirection)
		{
			if(dup2(output_redirection, STDOUT_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close (output_redirection);
		}
		//close(master->pipe[1]);
	}
	else // handle middle commands
	{
		if (input_redirection)
		{
			if (dup2(input_redirection, STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close (input_redirection);
			//close (master->pipe[0]);
		}
		else
		{
			if (dup2(master->pipes[i - 1][0], STDIN_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close(master->pipe[0]);
		}
		if (output_redirection)
		{
			if (dup2(output_redirection, STDOUT_FILENO) == -1)
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close(output_redirection);
			//close(master->pipe[1]);
		}
		else
		{
			if (dup2(master->pipes[i][1], STDOUT_FILENO) == -1)	
				exit(err_msg("dup2 failed", 1, master) && free_master(master, 1));
			//close(master->pipe[1]);
		}
	}
	if (!close_pipes(master))
		exit(err_msg("could not close pipes", 1, master) && free_master(master, 1));
	if (!close_files(master, i))
		exit(err_msg("could not close files", 1, master) && free_master(master, 1));
	execve(master->commands[i]->cmd_path, master->commands[i]->cmd_array, master->env_array);
	/*
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
	//printf("command_cound = %d\n", master->cmd_count);
	if (!close_pipes(master))
		return(err_msg("could not close pipes", 0, master));
	//if (!close_files(master))
		//return(err_msg("could not close files", 0, master));
	int w = 0;
	int x = -1;
	while (++x < master->cmd_count)
	{
		//ft_printf_fd(2, "waiting %d\n", x);	
		waitpid(master->processes[x], &w, 0);
	}

	return (1);
}
