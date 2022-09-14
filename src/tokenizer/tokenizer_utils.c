#include "minishell.h"

/* Adds the characters between token_start & token_end to the tokens struct. */
void	extract_token(t_master *master, char *token_start, char *token_end)
{
	int			token_len;
	t_tokens	*new_token;
	int			i;

	token_len = (token_end - token_start) + 1;
	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		exit(err_msg("malloc fail [extract_token()][1]", 1, master));
	init_token_values(new_token);
	if (master->tokens == NULL)
		master->tokens = new_token;
	else
	{
		new_token->previous = get_last_token(master->tokens);
		get_last_token(master->tokens)->next = new_token;
	}
	new_token->token = malloc(sizeof(char) * (token_len + 1));
	if (!new_token->token)
		exit(err_msg("malloc fail [extract_token()][2]", 1, master));
	i = -1;
	while (++i < token_len)
		new_token->token[i] = token_start[i];
	new_token->token[i] = '\0';
}

/* Initializes the values of the token structure passed as parameter. */
void	init_token_values(t_tokens *token)
{
	token->token_had_quotes = 0;
	token->token_type = 0;
	//token->word_splitted = 0;
	token->was_expanded = 0;
	token->quotes_removed = 0;
	token->was_isolated = 0;
	token->was_split = 0;
	token->next = NULL;
	token->previous = NULL;
}

/* Initialize the variables that are used in the tokenizer() function. */
void	init_tokenizer_helpers(t_tokenizer_helpers *t, char *line)
{
	t->token_start = 0;
	t->position = 0;
	t->quote_match_found = 0;
	t->last_token_end = -1;
	t->line = line;
}

/* Returns a pointer to the last token of the tokens structure. */
t_tokens	*get_last_token(t_tokens *tokens_list)
{
	t_tokens	*current;

	current = tokens_list;
	while (current && current->next)
		current = current->next;
	return (current);
}
