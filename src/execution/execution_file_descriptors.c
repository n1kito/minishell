#include "minishell.h"
//
// TODO protect IO_NUMBERS during syntax/other checks, they should be an int.

int	set_up_file_descriptors(t_master *master)
{
	if (!allocate_fds(master)
		|| !open_fds(master))
		// TODO !setup_heredoc(master) ?
		// Je sais pas encore trop comment gerer les delimiters
		return (0);
	return (1);
}

int	allocate_file_descriptors(t_msater *master)
{
	int			i;
	int			files_in_segment;
	t_tokens	*current;

	current = master->tokens;
	i = 0;
	while (i < master->cmd_count)
	{
		master->commands[i]->redirections_count = count_files_in_segment(master, i);
		master->commands[i]->fds = malloc(sizeof(int) * master->commands[i]->redirections_count;
		if (!master->commands[i]->fds)
			return (err_msg("malloc failed [open_file_descriptors()]", 0, master"));
		i++;
	}
	return (1);
}

void	open_file_descriptors(t_master *master, t_tokens *token)
{
	
}

int		count_files_in_segment(t_master *master, int segment_index)
{
	int			i;
	int			count;
	t_tokens	*current;

	current = master->tokens;
	i = 0;
	while (current && i < segment_index)
	{
		if (current->token_type == PIPE_TOKEN)
			i++;
		current = current->next;
	}
	count = 0;
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == IO_NUMBER
			|| current->token_type == FILE_NAME)
			count++;
		current = current->next;
	}
	return (count);
}
