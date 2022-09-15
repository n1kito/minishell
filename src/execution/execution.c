/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:42:35 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 11:43:20 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_open_heredoc(t_master *master, int i)
{
	if (master->commands[i]->heredoc_path)
	{
		master->commands[i]->heredoc_fd \
			= open(master->commands[i]->heredoc_path, O_RDONLY);
		if (master->commands[i]->heredoc_fd == -1)
		{
			perror(master->commands[i]->heredoc_path);
			return (0);
		}
		if (unlink(master->commands[i]->heredoc_path) == -1)
		{
			perror(master->commands[i]->heredoc_path);
			return (0);
		}
	}
	return (1);
}

/* Opens all necessary files and plugs pipes accordingly.
 * Builtin functions are launched without execve(). */
void	launch_exec(t_master *master, int i)
{
	int	input_redirection;
	int	output_redirection;

	if (!open_file_descriptors(master, i) || !process_open_heredoc(master, i))
		exit(free_all(master, 1));
	if (master->commands[i]->cmd_array[0])
	{
		if (!is_builtin_function(master->commands[i]->cmd_array[0]))
		{
			if (!command_error_check(master->commands[i], master))
			{
				close_pipes_and_files(master, i);
				exit(free_all(master, master->commands[i]->error_code));
			}
		}
	}
	input_redirection = last_input_fd(master, i);
	output_redirection = last_output_fd(master, i);
	plug_pipes(master, i, input_redirection, output_redirection);
	close_pipes_and_files(master, i);
	if (!master->commands[i]->cmd_array[0])
		exit(free_all(master, 0));
	if (is_builtin_function(master->commands[i]->cmd_array[0]))
		if (run_builtin(master, i))
			exit(free_all(master, 0));
	if (!is_builtin_function(master->commands[i]->cmd_array[0])
		&& env_for_exe(master))
		execve(master->commands[i]->cmd_path,
			master->commands[i]->cmd_array, master->env_for_exec);
	exit(free_all(master, 1));
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
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (master->processes[i] == 0)
		{
			setup_signals(*master->sa, &set_command_signal);
			launch_exec(master, i);
		}
		i++;
	}
	close_pipes(master);
	process_waiter(master);
	return (1);
}
