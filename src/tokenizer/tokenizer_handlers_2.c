#include "../../include/tokenizer.h"

/* Called when '$' character is found. Extracts preceding token if necessary. */
void	start_expansion_token(t_tokenizer_helpers *t, t_tokens **tokens)
{
	if (follows_open_token(t))
	{
		extract_token(tokens, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->token_start = t->position;
	t->position++;
}

/* Called on operator character. Extracts preceding token if necessary. */
void	start_operator_token(t_tokenizer_helpers *t, t_tokens **tokens)
{
	if (follows_open_token(t))
	{
		extract_token(tokens, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->token_start = t->position;
	t->position++;
}

/* Called when the current operator token can no longer be appended to. */
void	close_operator_token(t_tokenizer_helpers *t, t_tokens **tokens)
{
	extract_token(tokens, &t->line[t->token_start], &t->line[t->position - 1]);
	if (t->position)
		t->last_token_end = t->position - 1;
	t->token_start = t->position;
}
