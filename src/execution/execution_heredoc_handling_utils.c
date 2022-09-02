#include "minishell.h"

int	set_heredoc_path(t_master *master, int i)
{
	char	*heredoc_index;

	if (master->commands[i]->heredoc_path)
		return (1);
	heredoc_index = ft_itoa(i);
	master->commands[i]->heredoc_path
		= ft_strjoin("/tmp/heredoc_", heredoc_index);
	if (!master->commands[i]->heredoc_path)
		return (err_msg("malloc failed [set_heredoc_path()]",
				0, master));
	free(heredoc_index);
	return (1);
}

int	open_heredoc(t_master *master, int i)
{
	if (master->commands[i]->heredoc_fd)
		if (close(master->commands[i]->heredoc_fd) == -1)
			return (err_msg("could not close fd [open_heredoc()]",
					0, master));
	master->commands[i]->heredoc_fd
		= open(master->commands[i]->heredoc_path,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (master->commands[i]->heredoc_fd == -1)
		return (err_msg("open() failed [open_heredoc()]", 0, master));
	return (1);
}
