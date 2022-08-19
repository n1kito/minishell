#include "minishell.h"

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
int	expander(t_tokens **tokens, t_env *env)
{
	t_tokens	*current;
	t_expand	*expansions;

	expansions = NULL;
	current = *tokens;
	while (current)
	{
		if (!has_solitary_quote(current->token))
			return (0);
		if (current->token_type != DELIMITER)
		{
			if (!log_expansions(current->token, env, &expansions))
				return (err_msg("Failed to log expansions [expander()]", 0));
			if (expansions)
				if (!expand_token(current, expansions)
					|| !free_expansions(&expansions))
					return (err_msg("Failed to expand [expander()]", 0));
		}
		if (!process_and_remove_quotes(current))
			return (0);
		check_for_invisible_token(current);
		current = current->next;
	}
	return (1);
}

/* Goes through token and removes pairs of quotes. */
int	process_and_remove_quotes(t_tokens *token_node)
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
			if (!remove_quotes(&token_node, i, matching_quote_pos))
				return (0);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
	return (1);
}

/* Removes quote pairs from current token. */
int	remove_quotes(t_tokens **token_node, int first_quote, int second_quote)
{
	char	*concatenate_me;
	char	*tmp_token;
	char	*token;

	token = (*token_node)->token;
	concatenate_me = token + first_quote + second_quote + 1;
	token[first_quote + second_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][1]", 0));
	free(token);
	token = tmp_token;
	concatenate_me = token + first_quote + 1;
	token[first_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][2]", 0));
	free(token);
	token = tmp_token;
	(*token_node)->token = token;
	return (1);
}

/* Expands all expansions, back to front. */
int	expand_token(t_tokens *current, t_expand *expansions)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, &current->token[exp->name_end + 1]);
		if (!tmp_token)
			return (0);
		current->token[exp->start] = '\0';
		new_token = str_join(current->token, tmp_token);
		if (!new_token)
			return (0);
		free(tmp_token);
		tmp_token = current->token;
		current->token = new_token;
		free(tmp_token);
		exp = exp->next;
	}
	return (1);
}

/* If the token passed as parameter is of type WORD, is empty
 * and did not initially have empty quotes in it, it will be 
 * typed as INVISIBLE. */
void	check_for_invisible_token(t_tokens *token)
{
	if (token->token_type == WORD
		&& token->token[0] == '\0'
		&& !token->token_had_quotes)
		token->token_type = INVISIBLE;
}
