#include "../../include/tokenizer.h"

/* Called when EOL character is found in line */
void	handle_end_of_line(t_tokenizer_helpers *t, t_tokens **tokens)
{
	if (follows_open_token(t))
	{
		extract_token(tokens, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->position++;
}

/* Called when quote character is found. Will look for matching quote char
 * and divide tokens accordingly. */
void	handle_quotes(t_tokenizer_helpers *t)
{
	t->quote_match_found = find_matching_quote(&t->line[t->position]);
	if (t->quote_match_found)
		t->position += t->quote_match_found;
	t->position++;
}

/* Called when blank char is found. Extracts preceding token if necessary. */
void	handle_blank_char(t_tokenizer_helpers *t, t_tokens **tokens)
{
	if (follows_open_token(t))
	{
		extract_token(tokens, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->position++;
	t->token_start = t->position;
}
