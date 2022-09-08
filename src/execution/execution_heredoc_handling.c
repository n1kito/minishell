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
			if (!set_heredoc_path(master, i)
				|| !open_heredoc(master, i))
				return (0);
			if (!heredoc_process(master, current, i))
				return (0);
			//TODO: protext close and open below
			close(master->commands[i]->heredoc_fd);
			master->commands[i]->heredoc_fd
				= open(master->commands[i]->heredoc_path, O_RDONLY);
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
		return (err_msg("fork failed [setup_heredocs()]", 0, master));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (heredoc_process == 0)
	{
		setup_signals(*master->sa, &set_heredoc_signal);
		read_heredoc(current, master->commands[i], master, i);
	}
	if (waitpid(heredoc_process, &g_minishexit, 0) == -1)
		return (err_msg("waitpid() failed [setup_heredocs()]", 0, master));
	setup_signals(*master->sa, &signal_handler);
	g_minishexit = WEXITSTATUS(g_minishexit);
	if (g_minishexit == 0 || g_minishexit == 130 || g_minishexit == 131)
	{
		close_and_unlink_heredocs(master);
		return (0);
	}
	else
		close_heredocs(master);
	return (1);
}

/* Called when there is a problem with heredocs or when a CTRL + C signal
 * is caught. If so, everything is freed from this process it returns 
 * an exit code 0 that is caught by the parent process and that process
 * then knows to go back to the prompt. */
int	exit_gnl(t_master *master, char *line, int return_code)
{
	free(line);
	close_and_unlink_heredocs(master);
	clean_env(&master->env, 0);
	free_master(master, 0);
	return (return_code);
}

/* The heredoc read loop. Will continually get_next_line until line
 * is either only the delimiter, or is completely empty, meaning an
 * EOL character was found. */
void	read_heredoc(t_tokens *token, t_command *cmd_node, t_master *master, int i)
{
	char	*line;
	char	*delimiter;
	int		should_expand;

	delimiter = token->next->token;
	check_if_heredoc_should_expand(token->next, &should_expand);
	while (1)
	{
		line = readline("> ");
		if (g_minishexit == 130)
		{
			exit_gnl(master, line, 0);
			exit(g_minishexit);
		}
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(line))))
		{
			print_heredoc_warning(line, delimiter);
			free(line);
			line = NULL;
			rl_clear_history(); // TODO check if this is necessary
			close_heredocs(master);
			exit(clean_env(&master->env, 1) && free_master(master, 1));
		}
		if (should_expand && !expand_heredoc_line(&line, master))
			exit(exit_gnl(master, line, 0) || free_master(master, 0)); // pas sur des return codes ici... a tester !!!
		if (!heredoc_file_access(master, i, line))
			exit(exit_gnl(master, line, 0) || free_master(master, 0));
		write(cmd_node->heredoc_fd, line, ft_strlen(line));
		write(cmd_node->heredoc_fd, "\n", 1);
		free(line);
		line = NULL;
	}
}

/* Will process the expansions in the line passed as parameter. */
int	expand_heredoc_line(char **line, t_master *master)
{
	if (!log_heredoc_expansions(*line, master))
		return (err_msg("failed to log HERE_DOC expansions", 0, master));
	if (master->expansions)
		if (!expand_line(line, master->expansions))
			return (err_msg("failed to expand HERE_DOC", 0, master));
	free_expansions(&master->expansions);
	return (1);
}

/* Goes through heredoc line and logs all candidates for expansion. */
int	log_heredoc_expansions(char *line, t_master *master)
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
				return (0);
		}
		i++;
	}
	return (1);
}

/* Prints out warning when a heredoc is not delimited by the delimiter
 * but by an EOF (CTRL + D). */
// TODO: check that this warning does print out to stdout and not stderr
void	print_heredoc_warning(char *line, char *delimiter)
{
	char	*tmp_message;
	char	*warning;

	if (line)
		return ;
	// TODO protext strjoini
	tmp_message = ft_strjoin("mini(s)hell: warning: here-document \
delimited by end-of-file (wanted '", delimiter);
	warning = ft_strjoin(tmp_message, "')\n");
	free (tmp_message);
	ft_printf_fd(1, "%s", warning);
	free(warning);
}
