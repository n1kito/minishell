/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_array_exports.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:30:25 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/14 11:32:48 by vrigaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Logs commands in command structures.
 * Will only log the tokens marked WORD, and stop
 * each array when a pipe or the end of the list
 * is found. */
void	generate_command_structure(t_master *master)
{
	master->cmd_count = count_commands(master->tokens);
	create_command_structures(master, master->cmd_count);
	populate_command_structures(master, master->cmd_count);
}

/* Allocates space for the command arrays and initializes them. */
void	create_command_structures(t_master *master, int cmd_count)
{
	int	i;

	master->commands = malloc(sizeof(t_command *) * (cmd_count + 1));
	if (!master->commands)
		exit(err_msg("malloc failed [init_command_structures()][1]", 1, master)
			&& free_all(master, 1));
	i = 0;
	while (i < cmd_count)
	{
		master->commands[i] = NULL;
		master->commands[i] = malloc(sizeof(t_command));
		if (!master->commands[i])
			exit(err_msg("malloc failed [init_command_structures()][2]", 1, \
				master) && free_all(master, 1));
		master->commands[i]->cmd_array = NULL;
		master->commands[i]->cmd_path = NULL;
		master->commands[i]->error_code = 0;
		master->commands[i]->fds = NULL;
		master->commands[i]->heredoc_fd = -1;
		master->commands[i]->heredoc_path = NULL;
		master->commands[i]->redirections_count = 0;
		i++;
	}
	master->commands[i] = NULL;
}

/* Creates command subarrays for each command segment and populates
 * each one with the word tokens that make up the corresponding command. */
void	populate_command_structures(t_master *master, int cmd_count)
{
	int	i;
	int	words;

	master->next_command_start = master->tokens;
	i = 0;
	while (i < cmd_count)
	{
		words = count_words_in_segment(master);
		master->commands[i]->cmd_array = malloc(sizeof(char *) * (words + 1));
		if (!master->commands[i]->cmd_array)
			exit(err_msg("malloc failed [populate_command_structures()]", 1, \
				master) && free_all(master, 1));
		while (words >= 0)
			master->commands[i]->cmd_array[words--] = NULL;
		if (words)
			populate_nth_command_structure(master, i);
		i++;
	}
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
