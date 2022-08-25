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
void	init_master_structure(t_master *master, t_env *env)
{
	master->tokens = NULL;
	master->expansions = NULL;
	master->env = env;
	//init_env_structure(&master->env); // doing this by hand in the  main for now. Need to include env building function here.
	master->commands = NULL;
	master->env_array = NULL;
	master->next_command_start = NULL;
	master->latest_return_code = 0;
	master->malloc_ok = 1;
	master->printed_error_msg = 0;
}

/* Frees memory allocated for storingthe command arrays but not for the command themselves.
 * These are freed separately when freeing the tokens linked list. */
void	free_command_structures(t_master *master)
{
	int	i;

	i = 0;
	while (master->commands
			&& master->commands[i])
	{
		if (master->commands[i]->cmd_path)
			free(master->commands[i]->cmd_path);
		if (master->commands[i]->cmd_array)
			free(master->commands[i]->cmd_array);
		free(master->commands[i++]);
	}
	free(master->commands);
	master->commands = NULL;
}

/* Frees all malloced variables in the master structure. */
// TODO: Add freeing of the env.
int	free_master(t_master *master, int return_value)
{
	t_tokens	*current;
	t_tokens	*next_token;

	current = master->tokens;
	while (current)
	{
		next_token = current->next;
		free(current->token);
		free(current);
		current = next_token;
	}
	free_expansions(&master->expansions);
	if (master->commands)
		free_command_structures(master);
	return (return_value);
}