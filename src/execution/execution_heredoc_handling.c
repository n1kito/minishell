/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:10:42 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 18:30:45 by vrigaudy         ###   ########.fr       */
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

/* The heredoc read loop. Will continually get_next_line until line
 * is either only the delimiter, or is completely empty, meaning an
 * EOL character was found. */
void	read_heredoc(t_tokens *tok, t_command *cmd_nd, t_master *master, int i)
{
	char	*line;
	char	*tmp;
	char	*delimiter;
	int		tmp_minishexit;
	int		should_expand;

	tmp_minishexit = g_minishexit;
	g_minishexit = 0;
	delimiter = tok->next->tok;
	line = NULL;
	check_if_heredoc_should_expand(tok->next, &should_expand);
	rl_clear_history();
	while (1)
	{
		tmp = readline("> ");
		if (g_minishexit == 130)
			exit_heredoc(master, line, i, g_minishexit);
		if (tmp)
		{
			line = ft_strjoin(tmp, "\n");
			free(tmp);
		}
		else
			line = tmp;
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) \
			&& ft_strlen(line) - 1 == ft_strlen(delimiter)))
		{
			print_heredoc_warning(line, i, delimiter, master);
			exit_heredoc(master, line, i, 0);
		}
		if (should_expand)
			expand_heredoc_line(&line, master, i, tmp_minishexit);
		if (!heredoc_file_access(master, i))
			exit_heredoc(master, line, i, 1);
		write(cmd_nd->heredoc_fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
}

/* Prints out warning when a heredoc is not delimited by the delimiter
 * but by an EOF (CTRL + D). */
void	print_heredoc_warning(char *line, int cmdi, char *del, t_master *master)
{
	char	*tmp_message;
	char	*warning;

	if (line)
		return ;
	tmp_message = ft_strjoin("mini(s)hell: warning: here-document delimited by EOF (wanted '", \
		del);
	if (g_minishexit != 130)
	{
		warning = ft_strjoin(tmp_message, "')\n");
		if (!tmp_message || !warning)
		{
			exit(err_msg("malloc fail [print_heredoc_warning()]",
					1, master) && free_all(master, 1));
			exit_heredoc(master, line, cmdi, 1);
		}
		ft_printf_fd(1, "%s", warning);
		free(warning);
	}
	free (tmp_message);
	else
		printf("\n");
}
