/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:28:04 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 17:35:06 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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

void	plug_pipes(t_master *master, int i, int infile, int outfile)
{
	if (i == 0)
		plug_first_cmd(master, i, infile, outfile);
	else if (i == master->cmd_count - 1)
		plug_last_cmd(master, i, infile, outfile);
	else
		plug_middle_cmd(master, i, infile, outfile);
}

/* Loops through all heredocs in the command line, closes them and unlinks
 * the files. */
void	close_heredocs(t_master *master)
{
	int		i;

	i = -1;
	// TODO DOUBLE CHECK BUT I THINK THIS ONE IS NOT USED ANYWHERE
	while (++i < master->cmd_count)
	{
		if (master->commands[i]->heredoc_fd)
		{
			if (close(master->commands[i]->heredoc_fd) == -1)
				exit(err_msg("could not close heredoc [close_heredocs()]",
						1, master) && free_all(master, 1));
		}
	}
}

int	close_and_unlink_heredocs(t_master *master)
{
	int		i;

	i = -1;
	//TODO not sure I'm using this one
	while (++i < master->cmd_count)
	{
		if (master->commands[i]->heredoc_fd)
		{
			if (close(master->commands[i]->heredoc_fd) == -1)
				return (err_msg \
					("could not close heredoc [close_and_unlink_heredocs()]", \
					0, master));
			if (access(master->commands[i]->heredoc_path, F_OK) == 0 \
				&& unlink(master->commands[i]->heredoc_path) == -1)
				return (err_msg \
					("could not unlink heredoc [close_and_unlink_heredocs()]", \
					0, master));
		}
	}
	return (1);
}
