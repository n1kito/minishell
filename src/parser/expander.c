#include "minishell.h"

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
void	expander(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->token_type != DELIMITER)
			expand_token(current, master);
		if (!current->token[0] && current->token_type == WORD
			&& !current->token_had_quotes)
			current->token_type = INVISIBLE;
		else if (token_has_unquoted_blanks(current)
			&& current->token_type == WORD)
			process_for_word_splitting(&current, master);
		else
			process_and_remove_quotes(current, master);
		current = get_next_unsplitted_token(current);
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
		if (token->token_type == WORD
			&& token->token[0] == '\0'
			&& !token->token_had_quotes)
			token->token_type = INVISIBLE;
		current = current->next;
	}
}
