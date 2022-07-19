#include "../../include/tokenizer.h"

/* Initialize the variable that are used in the tokenizer() function. */
void	init_tokenizer_helpers(t_tokenizer_helpers *t, char *line)
{
	t->token_start = 0;
	t->position = 0;
	t->quote_match_found = 0;
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

/* Adds the characters between token_start & token_end to the tokens struct. */
// TODO: Remove this comment
// Possible to add PLUS keyword at start of function to see where and when
// a new node is created. Check header.
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

// TODO Remove this one, it's in the libft
int	ft_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}
