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

void	isolate_unquoted_expands(t_tokens *token_ptr, t_master *master)
{
	int	i;

	i = 0;
	while (token_ptr->token[i])
	{
		if (is_quote_character(token_ptr->token[i]))
			i += find_matching_quote(&token_ptr->token[i]) + 1;
		else if (token_ptr->token[i] == '$'
			&& !is_quote_character(token_ptr->token[i + 1]))
			handle_expand_extraction(token_ptr, &i, master);
		else
			i++;
	}
}

void	handle_expand_extraction(t_tokens *token_ptr, int *i, t_master *master)
{
	if (*i && !follows_unquoted_expand(token_ptr, *i))
	{
		split_previous_token(token_ptr, *i, master);
		token_ptr = token_ptr->next;
		token_ptr->was_isolated = 1;
		*i = 0;
	}
	*i += go_to_end_of_expand_name(token_ptr, *i);
	if (token_ptr->token[*i])
	{
		token_ptr->was_isolated = 1;
		split_previous_token(token_ptr, *i, master);
		token_ptr = token_ptr->next;
		token_ptr->was_isolated = 0;
		*i = 0;
	}
	else
		token_ptr->was_isolated = 1;
}

int	follows_unquoted_expand(t_tokens *token_ptr, int i)
{
	if (i && is_unquoted_expand(token_ptr, 0))
		return (1);
	return (0);
}

void	split_previous_token(t_tokens *token_to_split, int i, t_master *master)
{
	t_tokens	*new_token;
	t_tokens	*tmp_next;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		exit(err_msg("malloc fail [split_token()]", 1, master)
			&& free_all(master, 1));
	new_token->token = ft_strdup(&token_to_split->token[i]);
	if (!new_token->token)
		exit(err_msg("malloc fail [split_previous_token()]", 1, master)
			&& free_all(master, 1));
	new_token->token_type = WORD;
	new_token->token_id = token_to_split->token_id;
	new_token->token_type = token_to_split->token_type;
	new_token->split_id = token_to_split->split_id;
	new_token->was_split = 0;
	new_token->quotes_removed = 0;
	new_token->token_had_quotes = 0;
	token_to_split->token[i] = '\0';
	tmp_next = token_to_split->next;
	token_to_split->next = new_token;
	new_token->previous = token_to_split;
	new_token->next = tmp_next;
	if (new_token->next)
		new_token->next->previous = new_token;
}
