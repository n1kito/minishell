#include "minishell.h"

/* Takes master structer and converts command lines
 * and environment structures to arrays to be used
 * during execution. */
int	prep_execution_resources(t_master *master)
{
	if (!generate_command_structure(master)
		|| !set_up_file_descriptors(master))
		// set up fds and open necessary files -> how do we handle HEREDOCS ?
		// set up master path array: what happends if we delete the PATH between two prompts 
		// 		I think it should be redone everytime. Or we can update the path too
		// set up the binary path in each command node
/*		|| !convert_env_to_array(master))*/
		return (0);
	return (1);
}

/* Logs commands in command structures.
 * Will only log the tokens marked WORD, and stop
 * each array when a pipe or the end of the list
 * is found. */
int	generate_command_structure(t_master *master)
{
	master->cmd_count = count_commands(master->tokens);
	if (!create_command_structures(master, master->cmd_count)
		|| !populate_command_structures(master, master->cmd_count))
		return (0);
	return (1);
}

/* Allocates space for the command arrays and initializes them. */
int	create_command_structures(t_master *master, int cmd_count)
{
	int	i;

	master->commands = malloc(sizeof(t_command *) * (cmd_count + 1));
	if (!master->commands)
		return (err_msg("malloc failed [init_command_structures()][1]",
				0, master));
	i = 0;
	while (i < cmd_count)
	{
		master->commands[i] = NULL;
		master->commands[i] = malloc(sizeof(t_command));
		if (!master->commands[i])
			return (err_msg("malloc failed [init_command_structures()][2]",
					0, master));
		master->commands[i]->cmd_array = NULL;
		master->commands[i]->cmd_path = NULL;
		i++;
	}
	master->commands[i] = NULL;
	return (1);
}

/* Creates command subarrays for each command segment and populates
 * each one with the word tokens that make up the corresponding command. */
int	populate_command_structures(t_master *master, int cmd_count)
{
	int	i;
	int	word_count;

	master->next_command_start = master->tokens;
	i = 0;
	while (i < cmd_count)
	{
		word_count = count_words_in_segment(master);
		master->commands[i]->cmd_array = malloc(
				sizeof(char *) * (word_count + 1));
		if (!master->commands[i]->cmd_array)
			return (err_msg("malloc failed [populate_command_structures()]",
					0, master));
		while (word_count >= 0)
			master->commands[i]->cmd_array[word_count--] = NULL;
		if (word_count)
			populate_nth_command_structure(master, i);
		i++;
	}
	return (1);
}

/* Populates the nth command array with nth command segment arguments. */
void	populate_nth_command_structure(t_master *master, int command_index)
{
	int			i;
	t_tokens	*current;

	current = go_to_nth_segment(command_index, master->tokens);
	i = 0;
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == WORD)
			master->commands[command_index]->cmd_array[i++] = current->token;
		current = current->next;
	}
}
