/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_splitting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:17:19 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 12:03:32 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_isolater(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->token_type != DELIMITER)
			isolate_unquoted_expands(current, master);
		current = current->next;
	}
}

void	token_expander(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->token_type != DELIMITER)
			expand_token(current, master);
		current = current->next;
	}
}

void	expanded_token_splitter(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	if (is_only_blanks(current->token))
		{
			free(current->token);
			current->was_isolated = 1;
			current->was_split = 1;
			current->token = NULL;
		}
		else if (current->token && current->token[0] && token_has_blank(current->token) && current->was_isolated && current->was_split == 0)
		{
			split_token(current, master);
		}
		current = current->next;
}

void	token_merger(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->next
			&& (current->token_id == current->next->token_id)
			&& (current->was_split != current->next->was_split
				|| current->split_id > current->next->split_id))
					merge_token_with_next(current, master);
		else if (current->next
			&& current->token_id == current->next->token_id
			&& !current->was_split && !current->next->was_split)
				merge_token_with_next(current, master);
		else
			current = current->next;
	}
}

void	split_token(t_tokens *current, t_master *master)
{
	t_tokens	*split_tokens;

	split_tokens = NULL;
	split_tokens = split_expanded_token(&current, master);
	if (current->next)
	{
		current->next->previous = get_last_token(split_tokens);
		current->next->previous->next = current->next;
	}
	if (!current->previous)
	{
		free(current->token);
		free(current);
		master->tokens = split_tokens;
		current = master->tokens;
	}
	else
	{
		current->previous->next = split_tokens;
		split_tokens->previous = current->previous;
		free(current->token);
		free(current);
		current = split_tokens;
	}
}
