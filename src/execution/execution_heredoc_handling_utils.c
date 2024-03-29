/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_handling_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:26:41 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 17:27:23 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Sets the path of the heredoc file. Each command segment has a single
 * heredoc path that will be opened for each heredoc in the segment.
 * Different segments paths do not share a heredoc file. */
void	set_heredoc_path(t_master *master, int i)
{
	char	*heredoc_index;

	if (master->commands[i]->heredoc_path)
		return ;
	heredoc_index = ft_itoa(i);
	master->commands[i]->heredoc_path
		= ft_strjoin("/tmp/.heredoc", heredoc_index);
	if (!master->commands[i]->heredoc_path)
		exit(err_msg("malloc failed [set_heredoc_path()]",
				1, master) && free_all(master, 1));
	free(heredoc_index);
}

/* Closes heredoc fd before opening it again for write. */
void	open_heredoc(t_master *master, int i)
{
	if (master->commands[i]->heredoc_fd >= 0)
		if (close(master->commands[i]->heredoc_fd) == -1)
			exit(err_msg("could not close fd [open_heredoc()]", 1, master)
				&& free_all(master, 1));
	master->commands[i]->heredoc_fd
		= open(master->commands[i]->heredoc_path,
			O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (master->commands[i]->heredoc_fd == -1)
		exit(err_msg("open() failed [open_heredoc()]", 1, master)
			&& free_all(master, 1));
}

/* Checks if heredoc delimiter had quotes in it before quotes removal.
 * If so, the contents of the heredoc should not be expanded. */
void	check_if_heredoc_should_expand(t_tokens *delimiter, int *should_expand)
{
	if (delimiter->token_had_quotes)
		*should_expand = 0;
	else
		*should_expand = 1;
}

/* Check that the heredoc file is still accessible with write privileges. */
int	heredoc_file_access(t_master *master, int cmd_index)
{
	if (access(master->commands[cmd_index]->heredoc_path,
			F_OK | W_OK | R_OK) == -1)
	{
		return (err_msg("heredoc file error [heredoc_file_access()]",
				0, master));
	}
	return (1);
}

/* Will attempt to unlink all heredoc files created by the current process. */
int	unlink_heredocs(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->cmd_count)
	{
		if (master->commands[i]->heredoc_path)
			if (access(master->commands[i]->heredoc_path, F_OK) == 0)
				if (unlink(master->commands[i]->heredoc_path) == -1)
					return (err_msg \
						("could not unlink all heredoc files. careful!",
							0, master));
		i++;
	}
	return (1);
}
