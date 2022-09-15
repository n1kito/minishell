/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_splitting_merger.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:19:14 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:19:15 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_token_with_next(t_tokens *current)
{
	char		*tmp_token;
	t_tokens	*merged_token;

	tmp_token = current->token;
	merged_token = current->next;
	current->token = str_join(current->token, merged_token->token);
	current->was_isolated = merged_token->was_isolated;
	current->split_id = merged_token->split_id;
	current->was_split = merged_token->was_split;
	current->token_had_quotes = merged_token->token_had_quotes;
	free(tmp_token);
	free(merged_token->token);
	current->next = merged_token->next;
	if (current->next)
		current->next->previous = current;
	free(merged_token);
}
