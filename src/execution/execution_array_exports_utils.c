/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_array_exports_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:56:31 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 23:56:35 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterates through tokens to find the beginning of the nth command segment. */
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

/* Returns number of words in the next commmand segment. */
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

int	count_files_in_segment(t_master *master, int segment_index)
{
	int			count;
	t_tokens	*current;

	current = go_to_nth_segment(segment_index, master->tokens);
	count = 0;
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == FILE_NAME)
			count++;
		current = current->next;
	}
	return (count);
}
