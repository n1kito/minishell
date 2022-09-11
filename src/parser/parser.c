#include "../../include/minishell.h"

/* Goes through tokens and attributes the correct type for each. */
void	parser(t_tokens **tokens)
{
	t_tokens	*current;

	current = *tokens;
	while ((current))
	{
		if (!is_operator_token(current))
			if (!is_file_name_token(current))
				identify_token_type(current);
		current = current->next;
	}
}

/* Checks if current token is only numbers
 * and if previous and next token is a simple operator.*/
int	is_file_name_token(t_tokens *token)
{
	if (token->previous
		&& (token->previous->token[0] == '>'
			|| ((ft_strlen(token->previous->token) == 1
					&& token->previous->token[0] == '<'))))
	{
		token->token_type = FILE_NAME;
		return (1);
	}
	return (0);
}

/* Checks if current token is one of the operators
 * and gives it the appropriate code. */
int	is_operator_token(t_tokens *token)
{
	if (!is_operator(token->token[0]))
		return (0);
	if (ft_strlen(token->token) == 2)
	{
		if (token->token[0] == L_CHEVRON)
			token->token_type = HERE_DOC;
		else
			token->token_type = APPEND;
	}
	else
	{
		if (token->token[0] == L_CHEVRON)
			token->token_type = REDIRECT_FROM;
		else if (token->token[0] == R_CHEVRON)
			token->token_type = REDIRECT_TO;
		else
			token->token_type = PIPE_TOKEN;
	}
	return (1);
}

/* Receives token and assigns the correct token type. */
void	identify_token_type(t_tokens *token)
{
	t_tokens	*current;	

	current = token;
	if (current->previous && current->previous->token_type == HERE_DOC)
		current->token_type = DELIMITER;
	else if (current->token_type == TOKEN)
		current->token_type = WORD;
}
