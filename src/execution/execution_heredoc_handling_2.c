/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_handling_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrigaudy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:19:34 by vrigaudy          #+#    #+#             */
/*   Updated: 2022/09/14 23:14:04 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Goes through all tokens in the line and treat heredocs found one by one. */
int	setup_heredocs(t_master *master)
{
	t_tokens	*current;
	int			i;

	i = 0;
	current = master->tokens;
	while (current)
	{
		if (current->token_type == PIPE_TOKEN)
			i++;
		else if (current->token_type == HERE_DOC)
		{
			set_heredoc_path(master, i);
			if (!heredoc_process(master, current, i))
				return (0);
			if (g_minishexit == 130)
				return (1);
		}
		current = current->next;
	}
	return (1);
}

/* Process for opening heredocs. Called once per heredoc. Heredocs were
 * moved to process to allow for signal handling. */
int	heredoc_process(t_master *master, t_tokens *current, int i)
{
	int			heredoc_process;

	heredoc_process = fork();
	if (heredoc_process == -1)
		exit(err_msg("fork failed [setup_heredocs()]", 1, master)
			&& free_all(master, 1));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_process == 0)
	{
		setup_signals(*master->sa, &set_heredoc_signal);
		open_heredoc(master, i);
		read_heredoc(current, master->commands[i], master, i);
	}
	if (waitpid(heredoc_process, &g_minishexit, 0) == -1)
		exit(err_msg("waitpid() failed [setup_heredocs()]", 1, master)
			&& free_all(master, 1));
	setup_signals(*master->sa, &signal_handler);
	g_minishexit = WEXITSTATUS(g_minishexit);
	if (g_minishexit == 1)
	{
		unlink_heredocs(master);
		exit(free_all(master, 1));
	}
	return (1);
}

/* Will process the expansions in the line passed as parameter. */
void	expand_heredoc_line(char **line, t_master *master, int cmi, int tmp_m)
{
	int	tmp;

	tmp = g_minishexit;
	g_minishexit = tmp_m;
	log_heredoc_expansions(*line, cmi, master);
	if (master->expansions && !expand_line(line, master))
	{
		err_msg("failed to expand HERE_DOC", 0, master);
		exit_heredoc(master, *line, cmi, 1);
	}
	free_expansions(&master->expansions);
	g_minishexit = tmp;
}

/* Goes through heredoc line and logs all candidates for expansion. */
int	log_heredoc_expansions(char *line, int cmd_index, t_master *master)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$'
			&& line[i + 1]
			&& !is_blank_char(line[i + 1])
			&& !is_quote_character(line[i + 1])
			&& line[i + 1] != '\n')
		{
			if (!add_exp_node(master, line, i))
			{
				err_msg("failed to log HERE_DOC expansions\
					[log_heredoc_expansions()]", 0, master);
				exit_heredoc(master, line, cmd_index, 1);
			}
		}
		i++;
	}
	return (1);
}
