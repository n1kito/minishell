#include "minishell.h"

/* Looks through a command segment and returns the index
 * of the lastest input redirection node in the tokens. */
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

/* Looks through a command segment and returns the index
 * of the lastest output redirection node in the tokens. */
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

/* Loops through all heredocs in the command line, closes them and unlinks
 * the files. */
int	close_heredocs(t_master *master)
{
	int		i;

	i = -1;
	while (++i < master->cmd_count)
	{
		if (master->commands[i]->heredoc_fd)
		{
			if (close(master->commands[i]->heredoc_fd) == -1)
				return (err_msg("could not close heredoc [close_heredocs()]",
						0, master));
			if (unlink(master->commands[i]->heredoc_path) == -1)
				return (err_msg("could not unlink heredoc [close_heredocs()]",
						0, master));
		}
	}
	return (1);
}

/* Waits for all processes one by one and stores the exit code of the
 * latest function in the global g_minishexit variable. */
int	process_waiter(t_master *master)
{
	int	i;

	i = -1;
	while (++i < master->cmd_count)
		if (waitpid(master->processes[i], &g_minishexit, 0) == -1)
			return (err_msg("waitpid() failed [process_waiter()]", 0, master));
	g_minishexit = WEXITSTATUS(g_minishexit);
	return (1);
}