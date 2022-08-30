#include "minishell.h"

int	setup_file_descriptors(t_master *master)
{
	if (!allocate_file_descriptors(master)
		|| !setup_heredocs(master))
		return (0);
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

/* This function opens file descriptors and checks them immediately.
 * As soon as the loop encounters an error, the function stops opening files
 * for that segment and moves on to the next.
 * Errors are: for REDIRECT_TO or APPEND, filename cannot be a folder.
 * (for REDIRECT_FROM, filename can be a folder), or trying to read/write
 * to a file/folder we don't have permissions on. */
// TODO shorten this bullshit
// Actually this needs to be checked inside of the forks, because if you look
// at bash, the errors don't always appear in the same order.
int	open_file_descriptors(t_master *master, int i)
{
	int			j;
	t_tokens	*current;

	j = 0;
	current = go_to_nth_segment(i, master->tokens);
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == FILE_NAME)
		{
			if (current->previous->token_type == REDIRECT_TO
				|| current->previous->token_type == APPEND)
			{
				if (open(current->token, O_DIRECTORY) != -1)
				{
					ft_printf_fd(2, "%s: Is a directory\n", current->token);
					return (0);
				}
				else if (current->previous->token_type == REDIRECT_TO)
					master->commands[i]->fds[j] = open(current->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (current->previous->token_type == APPEND)
					master->commands[i]->fds[j] = open(current->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (access(current->token, F_OK) == 0
					&& access(current->token, W_OK) == -1)
				{
					ft_printf_fd(2, "%s: Permission denied\n", current->token);
					return (0);
				}
			}
			else if (current->previous->token_type == REDIRECT_FROM)
			{
				master->commands[i]->fds[j] = open(current->token, O_RDONLY);
				if (access(current->token, F_OK) == -1)
				{
					ft_printf_fd(2, "%s: No such file or directory\n", current->token);
					return (0);
				}
				else if (access(current->token, F_OK) == 0
						&& access(current->token, R_OK) == -1)
				{
					ft_printf_fd(2, "%s: Permission denied\n", current->token);
					return (0);
				}
			}
			j++;
		}	
		current = current->next;
	}
	return (1);
}
