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
			master->commands[i]->heredoc_fd
				= open("/tmp/", O_TMPFILE | O_RDWR, 0644);
			if (master->commands[i]->heredoc_fd == -1)
				return (0);
			read_heredoc(current, master->commands[i], master);
			// TODO I can't use TMP apparently, since when I write to it after GNL
			// the reading head moves to the end of the file. I need to open it again.
			lseek(master->commands[i]->heredoc_fd, 0, SEEK_SET);
		}
		current = current->next;
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
	tmp_message = ft_strjoin("\nmini(s)hell: warning: here-document delimited by end-of-file (wanted '", delimiter);
	warning = ft_strjoin(tmp_message, "')\n");
	free (tmp_message);
	ft_printf_fd(1, "%s", warning);
	free(warning);
}

/* The heredoc read loop. Will continually get_next_line until line
 * is either only the delimiter, or is completely empty, meaning an
 * EOL character was found. */
int	read_heredoc(t_tokens *token, t_command *command_node, t_master *master)
{
	char	*line;
	char	*delimiter;
	int		should_expand;

	delimiter = token->next->token;
	should_expand = 0;
	if (!token->next->token_had_quotes)
		should_expand = 1;
	while (1)
	{
		write(1, "> \r", 2);
		line = get_next_line(0);
		if (!line || (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
				&& ft_strlen(line) - 1 == ft_strlen(delimiter)))
		{
			free(line);
			get_next_line(-1);
			print_heredoc_warning(line, delimiter);
			return (1);
		}
		if (should_expand && !expand_heredoc_line(&line, master))
			return (0);
		write(command_node->heredoc_fd, line, ft_strlen(line));
		free(line);
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
