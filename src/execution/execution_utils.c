/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:12:52 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:53:22 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_and_files(t_master *master, int i)
{
	close_pipes(master);
	close_files(master, i);
}

void	close_pipes(t_master *master)
{
	int	i;

	i = 0;
	while (i < master->cmd_count - 1)
	{
		if (close(master->pipes[i][0]) == -1
			|| close(master->pipes[i][1]) == -1)
			exit(err_msg("could not close pipes [close_pipes()]",
					1, master) && free_all(master, 1));
		i++;
	}
	if (master->tmp_stdin >= 0)
		if (close(master->tmp_stdin) == -1)
			exit(err_msg("could not close tmp_stdin [close_pipes()]",
					1, master) && free_all(master, 1));
	if (master->tmp_stdout >= 0)
		if (close(master->tmp_stdout) == -1)
			exit(err_msg("could not close tmp_stdout [close_pipes()]",
					1, master) && free_all(master, 1));
}

void	close_files(t_master *master, int i)
{
	int	j;

	if (master->commands[i]->heredoc_path)
		if (close(master->commands[i]->heredoc_fd) == -1)
			exit(err_msg("heredoc close() failed [close_files()][1]", \
				1, master) && free_all(master, 1));
	if (master->commands[i]->redirections_count == 0)
		return ;
	j = 0;
	while (j < master->commands[i]->redirections_count)
	{
		if (master->commands[i]->fds[j])
			if (close(master->commands[i]->fds[j]) == -1)
				exit(err_msg("close() failed [close_files()][2]",
						1, master) && free_all(master, 1));
		j++;
	}
}

/* Checks if the string passed as parameter matches
 * the name of one of the builtins. */
int	is_builtin_function(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!name_len)
		return (0);
	if (ft_strcmp(name, "export") == 0
		|| ft_strcmp(name, "unset") == 0
		|| ft_strcmp(name, "echo") == 0
		|| ft_strcmp(name, "exit") == 0
		|| ft_strcmp(name, "env") == 0
		|| ft_strcmp(name, "pwd") == 0
		|| ft_strcmp(name, "cd") == 0)
		return (1);
	return (0);
}
