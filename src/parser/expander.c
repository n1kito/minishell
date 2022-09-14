#include "minishell.h"

int		only_blanks_left(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
		if (!is_blank_char(str[i]))
			return (0);
	return (1);
}

int		next_non_blank(char *str)
{
	int i;

	i = -1;
	while (str && str[++i])
		if (!is_blank_char(str[i]))
				break;
	return (i);
}

void	split_at_unquoted_blanks(t_tokens *token_ptr, t_master *master)
{
	int		i;
	char 	*token;
	char	*tmp;

	i = 0;
	token = token_ptr->token;
	while (token[i])
	{
		if (is_quote_character(token[i]))
			i += find_matching_quote(&token[i]) + 1;
		else if (is_blank_char(token[i]))
		{
			if (only_blanks_left(&token[i]))
				token[i] = '\0';
			else
			{
				split_previous_token(token_ptr, i, master);
				token_ptr = token_ptr->next;
				i = 0;
				tmp = token_ptr->token;
				token_ptr->token = ft_strdup(&token_ptr->token[next_non_blank(&token_ptr->token[i])]);
				free(tmp);
			}
		}
		else
			i++;
	}
}

void	add_token_ids(t_tokens *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token->token_id = i++;
		token->split_id = 0;
		token = token->next;
	}
}

void	check_for_quotes(t_tokens *tokens)
{
	int 		i;
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

int	token_has_blank(char *token)
{
	int i;

	i = -1;
	while(token[++i])
		if (is_blank_char(token[i]))
			return (1);
	return (0);
}

int	is_only_blanks(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' '
			&& str[i] != '	'
			&& str[i] != '\n')
			return (0);
	}
	return (1);
}

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
void	expander(t_master *master)
{
	t_tokens	*current;
	t_tokens *split_tokens = NULL;

	add_token_ids(master->tokens);
	current = master->tokens;
	while (current)
	{
		if (current->token_type != DELIMITER)
			isolate_unquoted_expands(current, master);
		current = current->next;
	}
	/*
	current = master->tokens;
	while (current)
	{
		printf("%s(%d)", current->token, current->token_had_quotes);
		if (current->next)
			printf("▒");
		else
			printf("\n");
		current = current->next;
	}
	*/
	check_for_quotes(master->tokens);
	current = master->tokens;
	while (current)
	{
		if (current->token_type != DELIMITER)
			expand_token(current, master);
		current = current->next;
	}
	current = master->tokens;
	while (current)
	{
		if (!current->was_isolated)
			process_and_remove_quotes(current, master);	
		current = current->next;
	}
	current = master->tokens;
	while (current)
	{
		//split_at_unquoted_blanks(current, master);
		if (is_only_blanks(current->token))
		{
			free(current->token);
			current->token = NULL;
		}
		else if (current->token && current->token[0] && token_has_blank(current->token) && current->was_isolated && current->was_split == 0)
		{
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
		//if (current->was_split == 0)
		current = current->next;
	}
	/*
	current = master->tokens;
	while (current)
	{
		printf("%s(i%d)[ID%d][S%dSID%d]", current->token, current->was_isolated, current->token_id, current->was_split, current->split_id);
		if (current->next)
			printf("▒");
		else
			printf("\n");
		current = current->next;
	}
	*/
	current = master->tokens;
	while (current)
	{
		//printf("[%s]\n", current->token);
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
	/*
	current = master->tokens;
	while (current)
	{
		printf("[%s][%d](len %d)", current->token, current->token_type, (int)ft_strlen(current->token));
		if (current->next)
			printf("|");
		else
			printf("\n");
		current = current->next;
	}
	*/
	check_for_invisible_tokens(master->tokens);
	/*
	current = master->tokens;
	while (current)
	{
		printf("[%s][%d](len %d)", current->token, current->token_type, (int)ft_strlen(current->token));
		if (current->next)
			printf("|");
		else
			printf("\n");
		current = current->next;
	}
	*/
	/*
	current = master->tokens;
	while (current)
	{
		printf("%s(type: %d | had_quotes: %d)", current->token, current->token_type, current->token_had_quotes);
		if (current->next)
			printf("▒");
		else
			printf("\n");
		current = current->next;
	}
	*/
	//identify_unquoted_expands(master);
}

void	merge_token_with_next(t_tokens *current)
{
	char 		*tmp_token;
	t_tokens	*merged_token;

	tmp_token = current->token;
	merged_token = current->next;
	current->token = ft_strjoin(current->token, merged_token->token);
	current->was_isolated = merged_token->was_isolated;
	current->split_id = merged_token->split_id; //not sure about this
	current->was_split = merged_token->was_split;
	current->token_had_quotes = merged_token->token_had_quotes;
	free(tmp_token);
	free(merged_token->token);
	current->next = merged_token->next;
	if (current->next)
		current->next->previous = current;
	free(merged_token);
}
t_tokens *split_expanded_token(t_tokens **token_ptr, t_master *master)
{
	int			i;
	char		**divided_token;
	t_master	tmp_master;
	t_tokens	*last_token;

	divided_token = ft_split_max((*token_ptr)->token, " 	\n");
	if (!divided_token)
		exit(err_msg("malloc fail [split_expanded_token()]", 1, master) && free_all(master, 1));
	tmp_master.tokens = NULL;
	i = -1;
	while (divided_token[++i])
	{
		extract_token(&tmp_master, divided_token[i], &divided_token[i][ft_strlen(divided_token[i])]);
		last_token = get_last_token(tmp_master.tokens);
		last_token->was_isolated = 1;
		last_token->split_id = i;
		last_token->was_split = 1;
		last_token->token_had_quotes = (*token_ptr)->token_had_quotes;
		last_token->token_id = (*token_ptr)->token_id;
		last_token->token_type = (*token_ptr)->token_type;
	}
	while (--i >= 0)
		free(divided_token[i]);
	free(divided_token);
	return (tmp_master.tokens);	
}

int	go_to_end_of_expand_name(t_tokens *current_ptr, int i)
{
	//printf("going to end of expand name\n");
	if (!ft_isalpha(current_ptr->token[i + 1])
		&& current_ptr->token[i + 1] != '_'
		&& current_ptr->token[i + 1] != '?')
		return (i + 1);
	i++;
	while (current_ptr->token[i]
			&& (ft_isalnum(current_ptr->token[i])
				|| current_ptr->token[i] == '_'
				|| current_ptr->token[i] == '?'))
		i++;
	return (i);
}

int	is_unquoted_expand(t_tokens *token_ptr, int i)
{
	if (token_ptr->token[i] == '$')
	{
		i++;
		if (ft_isalpha(token_ptr->token[i])
			|| token_ptr->token[i] == '_'
			|| token_ptr->token[i] == '?')
			return (1);
	}
	return (0);
}

int	follows_unquoted_expand(t_tokens *token_ptr, int i)
{
	//printf("follows expand\n");
	if (i && is_unquoted_expand(token_ptr, 0))
		return (1);
	return (0);
}

void	isolate_unquoted_expands(t_tokens *token_ptr, t_master *master)
{
	int 		i;
	
	i = 0;
	while (token_ptr->token[i])
	{
		if (is_quote_character(token_ptr->token[i]))		
			i += find_matching_quote(&token_ptr->token[i]) + 1;
		//else if (is_unquoted_expand(token_ptr, i))
		else if (token_ptr->token[i] == '$' && !is_quote_character(token_ptr->token[i + 1]))
		{
			if (i && !follows_unquoted_expand(token_ptr, i))
			{
				split_previous_token(token_ptr, i, master);
				token_ptr = token_ptr->next;
				token_ptr->was_isolated = 1;
				i = 0;
			}
			i += go_to_end_of_expand_name(token_ptr, i);
			if (token_ptr->token[i])
			{
				token_ptr->was_isolated = 1;
				split_previous_token(token_ptr, i, master);
				token_ptr = token_ptr->next;
				token_ptr->was_isolated = 0;
				i = 0;
			}
			else
				token_ptr->was_isolated = 1;
		}
		else
			i++;
	}
}

void	split_previous_token(t_tokens *token_to_split, int i, t_master *master)
{
	t_tokens	*new_token;
	t_tokens	*tmp_next;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		exit(err_msg("malloc fail [split_token()]", 1, master) && free_all(master, 1));
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

/* Goes through token and removes pairs of quotes. */
void	process_and_remove_quotes(t_tokens *token_node, t_master *master)
{
	int		i;
	int		matching_quote_pos;

	i = 0;
	while (token_node->token && token_node->token[i])
	{
		if ((token_node->token[i] == SINGLE_QUOTE || token_node->token[i] == DOUBLE_QUOTE)
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
void	remove_quotes(t_tokens **token_node, int quote1, int quote2, t_master *m)
{
	char	*concatenate_me;
	char	*tmp_token;

	concatenate_me = (*token_node)->token + quote1 + quote2 + 1;
	(*token_node)->token[quote1 + quote2] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][1]", 1, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
	concatenate_me = (*token_node)->token + quote1 + 1;
	(*token_node)->token[quote1] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		exit(err_msg("malloc() failed [remove_quotes()][2]", 1, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
}

/* Expands all expansions, back to front. */
int	expand_line(char **line, t_master *master)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = master->expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, *line + exp->name_end + 1);
		if (!tmp_token)
			return (0);
		*(*line + exp->start) = '\0';
		new_token = str_join(*line, tmp_token);
		if (!new_token)
		{
			free(tmp_token);
			return (0);
		}
		free(tmp_token);
		tmp_token = *line;
		*line = new_token;
		free(tmp_token);
		exp = exp->next;
	}
	return (1);
}

/* If the token passed as parameter is of type WORD, is empty
 * and did not initially have empty quotes in it, it will be 
 * typed as INVISIBLE. */
void	check_for_invisible_tokens(t_tokens *token)
{
	t_tokens *current;

	current = token;
	while (current)
	{
		if ((int)ft_strlen(current->token) == 0
			&& !current->token_had_quotes)
				current->token_type = INVISIBLE;
		current = current->next;
	}
}
