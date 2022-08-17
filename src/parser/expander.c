#include "../../include/minishell.h"

/* Removes quote pairs from current token. */
void	remove_quotes(t_tokens **token_node, int first_quote, int second_quote)
{
	char	*concatenate_me;
	char	*tmp_token;
	char	*token;

	token = (*token_node)->token;
	concatenate_me = token + first_quote + second_quote + 1;
	token[first_quote + second_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	token = tmp_token;
	concatenate_me = token + first_quote + 1;
	token[first_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	token = tmp_token;
	(*token_node)->token = token;
}

/* Logs new node in expansion structure to track expansions, their positions and
 * values (if found in env). Note that they are added LIFO. */
void	add_exp_node(t_expand **expansions, char *token, int i, t_env *env)
{
	t_expand	*new_expand;

	new_expand = malloc(sizeof(t_expand));
	if (!new_expand)
		return ;
	new_expand->start = i;
	new_expand->name_start = i + 1;
	new_expand->name_len = expansion_name_len(token + i);
	new_expand->name_end = i + new_expand->name_len;
	new_expand->name = token + new_expand->name_start;
	new_expand->value = search_env(env, new_expand->name,
			new_expand->name_len);
	new_expand->next = NULL;
	if (*expansions == NULL)
		*expansions = new_expand;
	else
	{
		new_expand->next = *expansions;
		*expansions = new_expand;
	}
}

/* Expands all expansions, back to front. */
void	expand_token(t_tokens *current, t_expand *expansions)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, &current->token[exp->name_end + 1]);
		current->token[exp->start] = '\0';
		new_token = str_join(current->token, tmp_token);
		free(tmp_token);
		tmp_token = current->token;
		current->token = new_token;
		free(tmp_token);
		exp = exp->next;
	}
}

/* Goes through token and removes pairs of quotes. */
void	process_and_remove_quotes(t_tokens *token_node)
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
			remove_quotes(&token_node, i, matching_quote_pos);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
}

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
		if (!has_single_quote(current->token))
			return (0);
		if (current->token_type != DELIMITER)
		{
			log_expansions(current->token, env, &expansions);
			if (expansions)
			{
				expand_token(current, expansions);
				free_expansions(&expansions);
			}
		}
		process_and_remove_quotes(current);
		if (current->token_type == WORD
			&& current->token[0] == '\0' && !current->token_had_quotes)
			current->token_type = INVISIBLE;
		current = current->next;
	}
	return (1);
}
