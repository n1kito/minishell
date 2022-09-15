/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:18:09 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:18:11 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

/* Removes quote pairs from current token. */
void	remove_quotes(t_tokens **token_node, int quot1, int quot2, t_master *m)
{
	char	*concatenate_me;
	char	*tmp_token;

	concatenate_me = (*token_node)->token + quot1 + quot2 + 1;
	(*token_node)->token[quot1 + quot2] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][1]", 1, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
	concatenate_me = (*token_node)->token + quot1 + 1;
	(*token_node)->token[quot1] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][2]", 1, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
}
