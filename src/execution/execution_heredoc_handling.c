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
void	read_heredoc(t_tokens *token, t_command *cmd_node, t_master *master, int i)
{
	char	*line;
	char	*tmp;
	char	*delimiter;
	int		tmp_minishexit;
	int		should_expand;

	tmp_minishexit = g_minishexit;
	g_minishexit = 0;
	delimiter = token->next->token;
	line = NULL;
	check_if_heredoc_should_expand(token->next, &should_expand);
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
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
					&& ft_strlen(line) - 1 == ft_strlen(delimiter)))
		{
			print_heredoc_warning(line, i, delimiter, master);
			exit_heredoc(master, line, i, 0);
		}
		if (should_expand)
			expand_heredoc_line(&line, master, i, tmp_minishexit);
		if (!heredoc_file_access(master, i))
			exit_heredoc(master, line, i, 1);
		write(cmd_node->heredoc_fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
}

/* Will process the expansions in the line passed as parameter. */
void	expand_heredoc_line(char **line, t_master *master, int cmd_index, int tmp_minishexit)
{
	int	tmp;

	tmp = g_minishexit;
	g_minishexit = tmp_minishexit;
	log_heredoc_expansions(*line, cmd_index, master);
	if (master->expansions && !expand_line(line, master))
	{
		err_msg("failed to expand HERE_DOC", 0, master);
		exit_heredoc(master, *line, cmd_index, 1);
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
				return (0);
		}
		i++;
	}
	return (1);
}

/* Prints out warning when a heredoc is not delimited by the delimiter
 * but by an EOF (CTRL + D). */
void	print_heredoc_warning(char *line, int cmd_index, char *delimiter, t_master *master)
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
					0, master);
			exit_heredoc(master, line, cmd_index, 1);
		}
		free (tmp_message);
		ft_printf_fd(1, "%s", warning);
		free(warning);
	}
	else
		printf("\n");
}
