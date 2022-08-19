#include "minishell.h"

/* The tokenizer() function strictly follows the bash guidelines.
See README for more information. */
// TODO try to change while condition with while(line[t->position])
int	tokenizer(char *line, t_master *master, t_tokenizer_helpers *t)
{
	while (t->position <= (int)ft_strlen(line) && master->malloc_success == 1)
	{
		if (line[t->position] == '\0')
			handle_end_of_line(t, master);
		else if (can_form_operator(&line[t->token_start], &line[t->position]))
			t->position++;
		else if (is_operator(line[t->position - 1])
			&& !can_form_operator(&line[t->token_start], &line[t->position])
			&& t->last_token_end != t->position - 1)
			close_operator_token(t, master);
		else if (is_quote_character(line[t->position]))
			handle_quotes(t);
		else if (line[t->position] == '$')
			start_expansion_token(t);
		else if (is_operator(line[t->position]))
			start_operator_token(t, master);
		else if (is_blank_char(line[t->position]))
			handle_blank_char(t, master);
		else if (follows_word(line, t->position))
			t->position++;
		else
			t->token_start = t->position++;
	}
	return (master->malloc_success);
}

void	init_token_values(t_tokens *token)
{
	token->token_had_quotes = 0;
	token->token_type = 0;
	token->next = NULL;
	token->previous = NULL;
}

/* Adds the characters between token_start & token_end to the tokens struct. */
int	extract_token(t_master *master, char *token_start, char *token_end)
{
	int			token_len;
	t_tokens	*new_token;
	int			i;

	token_len = (token_end - token_start) + 1;
	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return (err_msg("malloc failed [extract_token()][1]", --master->malloc_success));
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
		return (err_msg("malloc failed [extract_token()][2]", --master->malloc_success));
	i = -1;
	while (++i < token_len)
		new_token->token[i] = token_start[i];
	new_token->token[i] = '\0';
	return (1);
}
