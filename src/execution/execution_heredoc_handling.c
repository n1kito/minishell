/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:10:42 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 01:24:32 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Called when there is a problem with heredocs or when a CTRL + C signal
 * is caught. If so, everything is freed from this process it returns
 * an exit code 0 that is caught by the parent process and that process
 * then knows to go back to the prompt. */
int	exit_heredoc(t_master *master, char *line, int cmd_index, int return_code)
{
	if (line)
		free(line);
	close(master->commands[cmd_index]->heredoc_fd);
	if (return_code == 1)
		unlink(master->commands[cmd_index]->heredoc_path);
	free_all(master, 0);
	exit(return_code);
}

char	*join_for_heredoc(t_master *master, char *line, int i)
{
	char	*tmp;

	tmp = readline("> ");
	if (g_minishexit == 130)
		exit_heredoc(master, line, i, g_minishexit);
	if (tmp)
	{
		line = ft_strjoin(tmp, "\n");
		if (!line)
		{
			exit(err_msg("malloc fail [join_for_heredoc()]",
					1, master) && free_all(master, 1));
			exit_heredoc(master, line, i, 1);
		}
	}
	if (tmp)
		free(tmp);
	else
		line = tmp;
	return (line);
}

/* The heredoc read loop. Will continually get_next_line until line
 * is either only the token->next->token, or is completely empty, meaning an
 * EOL character was found. */
void	read_heredoc(t_tokens *tk, t_command *cmi, t_master *master, int i)
{
	char	*l;
	int		tmp_minishexit;
	int		should_expand;

	tmp_minishexit = g_minishexit;
	g_minishexit = 0;
	check_if_heredoc_should_expand(tk->next, &should_expand);
	rl_clear_history();
	while (1)
	{
		l = NULL;
		l = join_for_heredoc(master, l, i);
		if (!l || (!ft_strncmp(l, tk->next->token, ft_strlen(tk->next->token)) \
			&& ft_strlen(l) - 1 == ft_strlen(tk->next->token)))
		{
			print_heredoc_warning(l, i, tk->next->token, master);
			exit_heredoc(master, l, i, 0);
		}
		if (should_expand)
			expand_heredoc_line(&l, master, i, tmp_minishexit);
		if (!heredoc_file_access(master, i))
			exit_heredoc(master, l, i, 1);
		write(cmi->heredoc_fd, l, ft_strlen(l));
		free(l);
	}
}

/* Prints out warning when a heredoc is not delimited by the delimiter
 * but by an EOF (CTRL + D). */
void	print_heredoc_warning(char *line, int i, char *delimiter, t_master *m)
{
	char	*tmp_message;
	char	*warning;

	if (line)
		return ;
	if (g_minishexit != 130)
	{
		tmp_message = ft_strjoin("mini(s)hell: warning: here-document \
delimited by end-of-file (wanted '", delimiter);
		warning = ft_strjoin(tmp_message, "')\n");
		if (!tmp_message || !warning)
		{
			err_msg("malloc fail [print_heredoc_warning()]",
				0, m);
			exit_heredoc(m, line, i, 1);
		}
		free (tmp_message);
		ft_printf_fd(1, "%s", warning);
		free(warning);
	}
	else
		printf("\n");
}
