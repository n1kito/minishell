#include "minishell.h"

int	setup_file_descriptors(t_master *master)
{
	if (!allocate_file_descriptors(master)
		|| !setup_heredocs(master))
		return (0);
	open_file_descriptors(master);
	return (1);
}

int	allocate_file_descriptors(t_master *master)
{
	int			i;
	int			j;

	i = 0;
	while (i < master->cmd_count)
	{
		master->commands[i]->redirections_count = count_files_in_segment(master, i);
		master->commands[i]->fds = malloc(sizeof(int) * master->commands[i]->redirections_count);
		if (!master->commands[i]->fds)
			return (err_msg("malloc failed [open_file_descriptors()]", 0, master));
		j = 0;
		while (j < master->commands[i]->redirections_count)
			master->commands[i]->fds[j++] = 0;
		i++;
	}
	return (1);
}

void	open_file_descriptors(t_master *master)
{
	int			i;
	int			j;
	t_tokens	*current;

	i = 0;
	j = 0;
	while (current)
	{
		if (current->token_type == PIPE_TOKEN)
		{
			i++;
			j = 0;
		}
		else if (current->token_type == FILE_NAME)
		{
			if (open(current->token, O_DIRECTORY) != -1)
			{
				master->commands[i]->fds[j] = -2;
				ft_printf_fd(2, "%s is a directory", current->token);
			}
			else if (current->previous->token_type == REDIRECT_TO)
				master->commands[i]->fds[j] = open(current->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (current->previous->token_type == REDIRECT_FROM)
				master->commands[i]->fds[j] = open(current->token, O_RDONLY);
			else if (current->previous->token_type == APPEND)
				master->commands[i]->fds[j] = open(current->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			j++;
		}	
		current = current->next;
	}
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
