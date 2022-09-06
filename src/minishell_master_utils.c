#include "minishell.h"

/* Goes through the tokens and frees every node. */
void	free_tokens_structure(t_master *master)
{
	t_tokens	 *current;
	t_tokens	*next_token;

	current = master->tokens;
	while (current)
	{
		next_token = current->next;
		free(current->token);
		free(current);
		current = next_token;
	}
}

/* Will free all mallocs() in master structure except for the env linked list,
 * which is the only structure that is used everytime we enter a command. */
void	clean_master_memory(t_master *master)
{
	if (master->commands)
		free_commands_structure(master);
	if (master->tokens)
		free_tokens_structure(master);
}


/* Frees memory allocated for storing the command arrays but not for the command themselves.
 * These are freed separately when freeing the tokens linked list. */
void	free_commands_structure(t_master *master)
{
	int	i;
	//int	j;

	i = 0;
	while (master->commands
			&& master->commands[i])
	{
		if (master->commands[i]->cmd_path
			&& master->commands[i]->cmd_path != master->commands[i]->cmd_array[0])
			free(master->commands[i]->cmd_path);
		free(master->commands[i]->cmd_array);
		if (master->commands[i]->heredoc_fd)
		{
			if (access(master->commands[i]->heredoc_path, F_OK | W_OK))
				if (!unlink(master->commands[i]->heredoc_path))
					err_msg("could not remove heredoc_file [free_command_structures()]", 0, master); // sometimes it removes the files even if they are chmod 0, I have no idea what is the fuck.
			free (master->commands[i]->heredoc_path);
		}
		if (master->commands[i]->fds)
			free(master->commands[i]->fds);
		free(master->commands[i++]);
	}
	free(master->commands);
	master->commands = NULL;
}

void	free_pipes(t_master *master)
{
	int i;

	i = 0;
	if (!master->pipes)
		return ;
	while (i < master->cmd_count - 1)
	{
		free(master->pipes[i]);
		master->pipes[i] = NULL;
		i++;
	}
	free(master->pipes);
	master->pipes = NULL;
}
