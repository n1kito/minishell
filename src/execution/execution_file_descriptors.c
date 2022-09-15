#include "minishell.h"

void	allocate_file_descriptors(t_master *master)
{
	int			i;
	int			j;

	i = 0;
	while (i < master->cmd_count)
	{
		master->commands[i]->redirections_count
			= count_files_in_segment(master, i);
		master->commands[i]->fds
			= malloc(sizeof(int) * master->commands[i]->redirections_count);
		if (!master->commands[i]->fds)
			exit(free_all(master, 1)
				&& err_msg("malloc failed [open_file_descriptors()]", 1, master));
		j = 0;
		while (j < master->commands[i]->redirections_count)
			master->commands[i]->fds[j++] = -1;
		i++;
	}
}

/* This function opens file descriptors and checks them immediately.
 * As soon as the loop encounters an error, the function stops opening files
 * for that segment and moves on to the next. */
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
				if (!check_output_file(master, current, i, j))
					return (0);
			}
			else if (current->previous->token_type == REDIRECT_FROM)
			{
				if (!check_input_file(master, current, i, j))
					return (0);
			}
			j++;
		}	
		current = current->next;
	}
	return (1);
}

/* Checks input files (REDIRECT_FROM) and outputs error if the file
 * does not exist or cannot be read. */
int	check_input_file(t_master *master, t_tokens *current, int i, int j)
{
	if(!current->token)
		ft_printf_fd(2, "FILE HAS NO NAME\n");
	master->commands[i]->fds[j] = open(current->token, O_RDONLY);
	if (access(current->token, F_OK) == -1)
	{
		perror(current->token);
		g_minishexit = 1;
		return (0);
	}
	else if (access(current->token, F_OK) == 0
		&& access(current->token, R_OK) == -1)
	{
		perror(current->token);
		g_minishexit = 1;
		return (0);
	}
	return (1);
}

/* Checks output files (APPEND and REDIRECT_TO) and outputs error if
 * the file is actually a directory or it exists but canno be written
 * to. */
int	check_output_file(t_master *master, t_tokens *current, int i, int j)
{
	char		*error_message;

	if (open(current->token, O_DIRECTORY) != -1)
	{
		error_message = ft_strjoin(current->token, ": Is a directory\n");
		//TODO protect strjoin
		ft_printf_fd(2, "%s", error_message);
		free(error_message);
		g_minishexit = 1;
		return (0);
	}
	else if (current->previous->token_type == REDIRECT_TO)
		master->commands[i]->fds[j]
			= open(current->token, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (current->previous->token_type == APPEND)
		master->commands[i]->fds[j]
			= open(current->token, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (access(current->token, F_OK) == 0
		&& access(current->token, W_OK) == -1)
	{
		perror(current->token);
		g_minishexit = 1;
		return (0);
	}
	return (1);
}
