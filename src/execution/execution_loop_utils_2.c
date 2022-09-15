/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:33:23 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/14 17:35:48 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Waits for all processes one by one and stores the exit code of the
 * latest function in the global g_minishexit variable. */
void	process_waiter(t_master *master)
{
	int	i;

	i = -1;
	while (++i < master->cmd_count)
	{
		if (waitpid(master->processes[i], &g_minishexit, 0) == -1)
			exit(err_msg("waitpid() failed [process_waiter()]", 1, master)
				&& free_master(master, 1));
		if (WIFEXITED(g_minishexit) && WEXITSTATUS(g_minishexit) == 42)
			exit(free_all(master, 1));
	}
	if (WIFEXITED(g_minishexit))
		g_minishexit = WEXITSTATUS(g_minishexit);
	else if (WIFSIGNALED(g_minishexit))
	{
		g_minishexit = WTERMSIG(g_minishexit) + 128;
		if (g_minishexit == 130)
			printf("\n");
		if (g_minishexit == 131)
			ft_putstr_fd("Quit (Core Dumped)\n", 2);
	}
	setup_signals(*master->sa, &signal_handler);
}
