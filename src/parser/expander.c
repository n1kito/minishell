/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:21:42 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 12:03:56 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printer(t_tokens *tokens)
{
	while (tokens)
	{
		printf("%s", tokens->token);
		if (tokens->next)
			printf("░");
		else
			printf("\n");
		tokens = tokens->next;
	}
}

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
void	expander(t_master *master)
{
	add_token_ids(master->tokens);
	expand_isolater(master);
	t_tokens *current = master->tokens;
	while (current)
	{
		printf("%s(i%d)[ID%d][S%dSID%d]", current->token, current->was_isolated, current->token_id, current->was_split, current->split_id);
		if (current->next)
			printf("▒");
		else
			printf("\n");
		current = current->next;
	}
	check_for_quotes(master->tokens);
	token_expander(master);
	quotes_remover(master);
	expanded_token_splitter(master);
	token_merger(master);
	//printer(master->tokens);
	check_for_invisible_tokens(master->tokens);
}
