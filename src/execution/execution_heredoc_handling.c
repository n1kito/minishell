#include "minishell.h"

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
			master->commands[i]->heredoc_fd = open("/tmp/", O_TMPFILE | O_RDWR, 0644); // j'ai une erreur ici mais je sais pas pourquoi.
			if (master->commands[i]->heredoc_fd == -1)
				return (0);
			read_heredoc(current, master->commands[i], master);
		}
		current = current->next;
	}
	return (1);
}

int	read_heredoc(t_tokens *heredoc_token, t_command *command_node, t_master *master)
{
	char	*line;
	char	*delimiter;
	int		should_expand;

	delimiter = heredoc_token->next->token;
	should_expand = 0;
	if (!heredoc_token->next->token_had_quotes)
		should_expand = 1;
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
			&& ft_strlen(line) - 1 == ft_strlen(delimiter))
		{
			free(line);
			get_next_line(-1);
			return (1);	
		}
		if (should_expand)
			if (!expand_heredoc_line(&line, master))
				return (0);
		write(command_node->heredoc_fd, line, ft_strlen(line));
		free(line);
	}
}

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
			if(!add_exp_node(master, line, i))
				return (0);
		}
		i++;
	}
	return (1);
}
