/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:17:54 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 11:19:08 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_remover(t_master *master)
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

/* Goes through tokens and sets a value to determine if
 * token had quotes before expansion/quote removal. */
void	check_for_quotes(t_tokens *tokens)
{
	int			i;
	t_tokens	*current;

	current = tokens;
	i = 0;
	while (current)
	{
		i = 0;
		while (current->token[i])
		{
			if ((current->token[i] == SINGLE_QUOTE
					|| current->token[i] == DOUBLE_QUOTE)
				&& find_matching_quote(current->token + i))
				current->token_had_quotes = 1;
			i++;
		}
		current = current->next;
	}
}

/* Goes through token and removes pairs of quotes. */
void	process_and_remove_quotes(t_tokens *token_node, t_master *master)
{
	int		i;
	int		matching_quote_pos;

	i = 0;
	while (token_node->token && token_node->token[i])
	{
		if ((token_node->token[i] == SINGLE_QUOTE
				|| token_node->token[i] == DOUBLE_QUOTE)
			&& find_matching_quote(token_node->token + i))
		{
			if (token_node->token_had_quotes == 0)
				token_node->token_had_quotes = 1;
			matching_quote_pos = find_matching_quote(token_node->token + i);
			remove_quotes(&token_node, i, matching_quote_pos, master);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
	token_node->quotes_removed = 1;
}

/* Removes quote pairs from current token. */
void	remove_quotes(t_tokens **token_ptr, int quote1, int quote2, t_master *m)
{
	char	*concatenate_me;
	char	*tmp_token;

	concatenate_me = (*token_ptr)->token + quote1 + quote2 + 1;
	(*token_ptr)->token[quote1 + quote2] = '\0';
	tmp_token = str_join((*token_ptr)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][1]", 1, m));
	free((*token_ptr)->token);
	(*token_ptr)->token = tmp_token;
	concatenate_me = (*token_ptr)->token + quote1 + 1;
	(*token_ptr)->token[quote1] = '\0';
	tmp_token = str_join((*token_ptr)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][2]", 1, m));
	free((*token_ptr)->token);
	(*token_ptr)->token = tmp_token;
}
