/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:58:54 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 13:58:58 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	isolate_loop(t_master *master)
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

void	expand_loop(t_master *master)
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

void	quotes_removal_loop(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (!current->was_isolated)
			process_and_remove_quotes(current, master);
		current = current->next;
	}
}

void	expanded_token_split_loop(t_master *master, t_tokens **split_tokens)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (is_only_blanks(current->token))
		{
			free(current->token);
			current->was_isolated = 1;
			current->was_split = 1;
			current->token = NULL;
		}
		else if (current->token && current->token[0]
			&& token_has_blank(current->token)
			&& current->was_isolated && current->was_split == 0)
			tok_splitter(current, split_tokens, master);
		current = current->next;
	}
}

void	merge_back_loop(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->next
			&& (current->token_id == current->next->token_id)
			&& (current->was_split != current->next->was_split
				|| current->split_id > current->next->split_id))
			merge_token_with_next(current);
		else if (current->next
			&& current->token_id == current->next->token_id
			&& !current->was_split && !current->next->was_split)
			merge_token_with_next(current);
		else
			current = current->next;
	}
}
