#include "minishell.h"

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
