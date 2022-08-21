#include "minishell.h"

/* Prints error message on stderr and returns error code passed as parameter. */
int	err_msg(char *error, int error_code, t_master *master)
{
	if (master->printed_error_msg++ == 0)
		ft_printf_fd(2, "Error\n");
	ft_printf_fd(2, "%s\n", error);
	return (error_code);
}

/* Initialises the master structure with correct values. */
void	init_master_structure(t_master *master, t_env *env)
{
	master->tokens = NULL;
	master->env = env;
	master->expansions = NULL;
	//init_env_structure(&master->env); // doing this by hand in the  main for now. Need to include env building function here.
	master->malloc_success = 1;
	master->printed_error_msg = 0;
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
	return (return_value);
}
