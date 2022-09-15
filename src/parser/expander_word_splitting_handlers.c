/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_splitting_handlers.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:11:46 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 12:10:55 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_token_with_next(t_tokens *current, t_master *master)
{
	char		*tmp_token;
	t_tokens	*merged_token;

	tmp_token = current->token;
	merged_token = current->next;
	current->token = str_join(current->token, merged_token->token);
	if (!current->token)
		exit(err_msg("malloc fail [merge_token_with_next()]", 1, master)
			&& free_all(master, 1));
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

void	split_previous_token(t_tokens *token_to_split, int i, t_master *master)
{
	t_tokens	*new_token;
	t_tokens	*tmp_next;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		exit(err_msg("malloc fail [split_token()]", 1, master)
			&& free_all(master, 1));
	new_token->token = ft_strdup(&token_to_split->token[i]);
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

void	isolate_unquoted_expands(t_tokens *token_ptr, t_master *master)
{
	int	i;

	i = 0;
	while (token_ptr->token[i])
	{
		if (is_quote_character(token_ptr->token[i]))
			i += find_matching_quote(&token_ptr->token[i]) + 1;
		else if (token_ptr->token[i] == '$'
			&& !is_quote_cexiharacter(token_ptr->token[i + 1]))
			isolate_expand(token_ptr, &i, master);
		else
			i++;
	}
}

void	isolate_expand(t_tokens *token_ptr, int *i, t_master *master)
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

t_tokens	*split_expanded_token(t_tokens **token_ptr, t_master *master)
{
	int			i;
	char		**divided_token;
	t_master	tmp_master;
	t_tokens	*last_token;

	divided_token = ft_split_max((*token_ptr)->token, " 	\n");
	if (!divided_token)
		exit(err_msg("malloc fail [split_expanded_token()]", 1, master)
			&& free_all(master, 1));
	tmp_master.tokens = NULL;
	i = -1;
	while (divided_token && divided_token[++i])
	{
		extract_token(&tmp_master, divided_token[i],
			&divided_token[i][ft_strlen(divided_token[i])]);
		last_token = get_last_token(tmp_master.tokens);
		last_token->was_isolated = 1;
		last_token->split_id = i;
		last_token->was_split = 1;
		last_token->token_had_quotes = (*token_ptr)->token_had_quotes;
		last_token->token_id = (*token_ptr)->token_id;
		last_token->token_type = (*token_ptr)->token_type;
	}
	free_split_tokens(divided_token);
	return (tmp_master.tokens);
}
