#include "minishell.h"

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
int	convert_to_array(t_master *master)
{
	if (!convert_commands_to_array(master))
/*		|| !convert_env_to_array(master))*/
		return (0);
	return (1);
}

/* Divides the tokens linked list into arrays.
 * Will only log the tokens marked WORD, and stop
 * each array when a pipe or the end of the list
 * is found. */
int	convert_commands_to_array(t_master *master)
{
	int	command_count;

	command_count = count_commands(master->tokens);
	if (!create_command_array(master, command_count)
		|| !create_command_subarrays(master, command_count))
		return (0);
	return (1);
}

/* Allocates space for the command arrays and initializes them. */
int	create_command_array(t_master *master, int cmd_count)
{
	int	i;

	master->command_array = malloc(sizeof(char **) * (cmd_count + 1));
	if (!master->command_array)
		return (err_msg("malloc failed [init_command_array()]", 0, master));
	i = 0;
	while (i <= cmd_count)
		master->command_array[i++] = NULL;
	return (1);
}

/* Creates command subarrays for each command segment and populates
 * each one with the word tokens that make up the corresponding command. */
int	create_command_subarrays(t_master *master, int cmd_count)
{
	int	i;
	int	word_count;

	master->next_command_start = master->tokens;
	i = 0;
	while (i < cmd_count)
	{
		word_count = count_words_in_segment(master);
		master->command_array[i] = malloc(sizeof(char *) * (word_count + 1));
		if (!master->command_array[i])
			return (err_msg("malloc failed [create_command_subarrays()]",
					0, master));
		while (word_count >= 0)
			master->command_array[i][word_count--] = '\0';
		if (word_count)
			populate_nth_command_array(master, i);
		i++;
	}
	return (1);
}

/* Populates the nth command array with nth command segment arguments. */
void	populate_nth_command_array(t_master *master, int command_index)
{
	int			i;
	t_tokens	*current;

	current = go_to_nth_segment(command_index, master->tokens);
	i = 0;
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == WORD)
			master->command_array[command_index][i++] = current->token;
		current = current->next;
	}
}
