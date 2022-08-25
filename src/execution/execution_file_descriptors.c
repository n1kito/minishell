#include "minishell.h"

int	open_file_descriptors(t_master *master)
{
	t_tokens	*current;
	int			file_count;
	
	current = master->tokens;
	// TODO move this bullshit to separate setup function
	master->file_fds = malloc(sizeof (int *) * (master->cmd_count + 1));
	if (master->file_fds == NULL)
		return (err_msg("malloc failed [open_file_descriptors()]", 0, master));
	// TODO malloc() space for each command segment FDs after counting them of course.
	return (1);
}

void	open_fd(t_master *master, t_tokens *token)
{

}
