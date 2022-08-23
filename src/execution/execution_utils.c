#include "minishell.h"

/* Converts the env linked list back to an array
 * of values following the *envp[] syntax of
 * VARIABLE=VALUE. */
// TODO Merge from Victor's work
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
		if (current->token_type == PIPE_TOKEN)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count + 1);
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

int	count_words_in_segment(t_master *master)
{
	int			count;
	t_tokens	*current;

	count = 0;
	current = master->next_command_start;
	while (current)
	{
		if (current->token_type == WORD)
			count++;
		else if (current->token_type == PIPE_TOKEN)
		{
			master->next_command_start = current->next;
			break ;
		}
		current = current->next;
	}
	return (count);
}  

t_tokens	*go_to_nth_segment(int i, t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (i && current)
	{
		if (current->token_type == PIPE_TOKEN)
			i--;
		current = current->next;
	}
	return (current);
}

void	populate_command_array(t_master *master, int command_index)
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
	// if the command segment is empty, should I make the pointer point to NULL ?
	// I'm afraid it would keep me from properly iterating of the command array to free it for example.
	// As is I don't have an issue when trying to access those areas.
	// if (i == 0)
	// 	master->command_array[command_index] = NULL;
}

/* Creates command arrays with the words that constitute each command. */
int	create_command_subarrays(t_master *master, int cmd_count)
{
	int i;
	int	word_count;

	master->next_command_start = master->tokens;
	i = 0;
	while (i < cmd_count) // could also be while (master->next_command_start ?)
	{
		word_count = count_words_in_segment(master);
		master->command_array[i] = malloc(sizeof(char *) * (word_count + 1));
		if (!master->command_array[i])
			return (err_msg("malloc failed [convert_commands_to_array][2]", 0, master));
		while (word_count >= 0)
			master->command_array[i][word_count--] = '\0';
		if (word_count)
			populate_command_array(master, i);
		i++;
	}
	// prints out each command array
	/*
	int j = 0;
	while (master->command_array[j])
	{
		printf("> ");
		if (master->command_array[j][0])
		{
			int k = 0;
			while (master->command_array[j][k])	
				printf("%s ", master->command_array[j][k++]);
		}
		else
			printf("no command found");
		printf("\n");
		j++;
	}
	*/
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
