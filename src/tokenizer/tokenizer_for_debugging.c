#include "../../include/tokenizer.h"

// These are duplicates of two functions used only for visualisation and
// debugging purposes.

/* The tokenizer() function strictly follows the shell guidelines.
See README for more information. */
void	tokenizer(char *line, t_tokens **tokens, t_tokenizer_helpers *t)
{
	while (t->position <= ft_strlen(line))
	{
		if (line[t->position] == '\0')
		{
			ONE
			handle_end_of_line(t, tokens);
		}
		else if (can_form_operator(&line[t->token_start], &line[t->position]))
		{
			TWO
			t->position++;
		}
		else if (is_operator(line[t->position - 1])
				&& !can_form_operator(&line[t->token_start], &line[t->position])
				&& t->last_token_end != t->position - 1)
		{
			THREE
			close_operator_token(t, tokens);
		}
		else if (is_quote_character(line[t->position]))
		{
			FOUR
			handle_quotes(t, tokens);
		}
		else if (line[t->position] == '$')
		{
			FIVE
			start_expansion_token(t, tokens);
		}
		else if (is_operator(line[t->position]))
		{
			SIX
			start_operator_token(t, tokens);
		}
		else if (is_blank_char(line[t->position]))
		{
			SEVEN
			handle_blank_char(t, tokens);
		}
		else if (follows_word(line, t->position, t->quote_match_found))
		{
			EIGHT
			t->position++;
		}
		else
		{
			TEN
			t->token_start = t->position++;
		}
	}
}

/* Adds the characters between token_start & token_end to the tokens struct. */
void	extract_token(t_tokens **tokens, char *token_start, char *token_end)
{
	int			token_len;
	t_tokens	*new_token;
	int			i;

	PLUS
	token_len = (token_end - token_start) + 1;
	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->token = malloc(sizeof(char) * (token_len + 1));
	if (!new_token->token)
		return ;
	i = -1;
	while (++i < token_len)
		new_token->token[i] = token_start[i];
	new_token->token[i] = '\0';
	new_token->next = NULL;
	if ((*tokens) == NULL)
		*tokens = new_token;
	else
		get_last_token(*tokens)->next = new_token;
}
