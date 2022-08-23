#include "minishell.h"

/* Converts the env linked list back to an array
 * of values following the *envp[] syntax of
 * VARIABLE=VALUE. */
int convert_env_to_array(t_master *master)
{
	(void)master;
	return (0);
}

/* Goes through tokens and counts the number of pipes.
 * The number of commands = pipe_count + 1. */
int	count_commands(t_tokens *tokens)
{
	int			pipe_count;
	t_tokens	*current;

	pipe_count = 0;
	current = tokens;
	while (current)
	{
		if (current->token_type = PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count + 1);
}

/* Allocates space for the command arrays and initializes them. */
int	init_command_array(t_master *master, int cmd_count)
{
	int	i;

	master->command_array = malloc(sizeof(char **) * (command_count + 1));
	if (!master->command_array)
		return (err_msg("malloc failed [init_command_array()]", 0, master));
	i = 0;
	while (i <= cmd_count)
		master->command_array[i++] = NULL;
	return (1);
}

/* Populates command arrays with the words that constitute each command. */
int	init_command_subarrays(t_master *master, int cmd_count)
{
	int i;

	i = 0;
	while (i < command_count)
	{
		command_array[i] = malloc(sizeof(char *) * (word_count + 1));
		if (!command_array[i])
			return (err_msg("malloc failed [convert_commands_to_array][2]", 0, master);
		command_array[i][word_cound] = '\0';
	}

}

/* Divides the tokens linked list into arrays.
 * Will only log the tokens marked WORD, and stop
 * each array when a pipe or the end of the list
 * is found. */
int	convert_commands_to_array(t_master *master)
{
	int	command_count;

	command_count = count_commands(master->tokens);
	if (!init_command_array(master, command_count))
		|| !init_command_subarrays(master, command_count))
		return (0);
	return (1);
}

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
int	convert_to_array(t_master *master)
{
	if (!convert_commands_to_array(master)
		|| !convert_env_to_array(master))
		return (0);
	return (1);
}
