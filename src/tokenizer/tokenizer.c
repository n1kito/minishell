#include "../../include/tokenizer.h"

/* The tokenizer() function strictly follows the shell guidelines.
See README for more information. */
void	tokenizer(char *line, t_tokens **tokens, t_tokenizer_helpers *t)
{
	while (t->position <= ft_strlen(line))
	{
		if (line[t->position] == '\0')
			handle_end_of_line(t, tokens);
		else if (is_operator(line[t->position - 1])
			&& can_form_operator(&line[t->token_start], &line[t->position]))
			t->position++;
		else if (is_operator(line[t->position - 1])
			&& !can_form_operator(&line[t->token_start], &line[t->position]))
			close_operator_token(t, tokens);
		else if (is_quote_character(line[t->position]))
			handle_quotes(t, tokens);
		else if (line[t->position] == '$')
			start_expansion_token(t, tokens);
		else if (is_operator(line[t->position]))
			start_operator_token(t, tokens);
		else if (is_blank_char(line[t->position]))
			handle_blank_char(t, tokens);
		else if (follows_word(line, t->position, t->quote_match_found))
			t->position++;
		else
			t->token_start = t->position++;
	}
}
