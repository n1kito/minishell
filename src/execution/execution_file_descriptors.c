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
			master->commands[i]->fds[j++] = 0; // should I init at -1 ? that's what I wrote in tokenizer.h
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
	current = master->tokens;
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
				master->commands[i]->fds[j] = -2; // An fd set to -2 means that the fd is a directory.
				ft_printf_fd(2, "%s is a directory", current->token); // this could be moved to the file_checker function in fork process.
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
