#include "minishell.h"

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
int	expander(t_master *master, t_env *env)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (!has_solitary_quote(current->token, master))
			return (0);
		if (current->token_type != DELIMITER)
		{
			if (!log_expansions(current->token, env, master))
				return (err_msg("failed to log expansions [expander()]",
						0, master));
			if (master->expansions)
				if (!expand_token(current, master->expansions))
					return (err_msg("failed to expand [expander()]",
							0, master));
		}
		free_expansions(&master->expansions);
		if (!process_and_remove_quotes(current, master))
			return (0);
		check_for_invisible_token(current);
		current = current->next;
	}
	return (1);
}

/* Goes through token and removes pairs of quotes. */
int	process_and_remove_quotes(t_tokens *token_node, t_master *master)
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
			if (!remove_quotes(&token_node, i, matching_quote_pos, master))
				return (0);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
	return (1);
}

/* Removes quote pairs from current token. */
int	remove_quotes(t_tokens **token_node, int quote1, int quote2, t_master *m)
{
	char	*concatenate_me;
	char	*tmp_token;

	concatenate_me = (*token_node)->token + quote1 + quote2 + 1;
	(*token_node)->token[quote1 + quote2] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][1]", 0, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
	concatenate_me = (*token_node)->token + quote1 + 1;
	(*token_node)->token[quote1] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][2]", 0, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
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
		{
			free(tmp_token);
			return (0);
		}
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
