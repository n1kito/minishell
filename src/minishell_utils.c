#include "minishell.h"

/* Prints error message on stderr and returns error code passed as parameter. */
int	err_msg(char *error, int error_code, t_master *master)
{
	if (master->printed_error_msg++ == 0)
		ft_printf_fd(2, "\033[1;31mError\033[0;39m\n");
	ft_printf_fd(2, "> %s\n", error);
	return (error_code);
}

/* Initialises the master structure with correct values. */
void	init_master_structure(t_master *master, char *envp[])
{
	master->tokens = NULL;
	// TODO ?? master->helpers = NULL;
	master->expansions = NULL;
	master->env = NULL;
	get_env(envp, &master->env);
	//init_env_structure(&master->env); // doing this by hand in the  main for now. Need to include env building function here.
	master->commands = NULL;
	master->processes = NULL;
	master->pipes = NULL;
	master->env_array = NULL;
	master->next_command_start = NULL;
	master->latest_exit_code = 0;
	master->malloc_ok = 1;
	master->printed_error_msg = 0;
}

/* Frees memory allocated for storingthe command arrays but not for the command themselves.
 * These are freed separately when freeing the tokens linked list. */
void	free_command_structures(t_master *master)
{
	int	i;
	//int	j;

	i = 0;
	while (master->commands
			&& master->commands[i])
	{
		//j = 0;
		//while (master->commands[i]->cmd_array && master->commands[i]->cmd_array[j])
		//	free(master->commands[i]->cmd_array[j++]);
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
		//if (master->commands[i]->cmd_array)
		//	free(master->commands[i]->cmd_array);
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

/* Frees all malloced variables in the master structure. */
// TODO: Add freeing of the env.
int	free_master(t_master *master, int return_value)
{
	t_tokens	*current;
	t_tokens	*next_token;

	if (master->commands)
		free_command_structures(master);
	current = master->tokens;
	while (current)
	{
		next_token = current->next;
		free(current->token);
		free(current);
		current = next_token;
	}
	master->tokens = NULL;
	free_expansions(&master->expansions);
	free_pipes(master);
	master->expansions = NULL;
	free(master->processes);
	master->processes = NULL;
	// add free function for pipes
	return (return_value);
}
