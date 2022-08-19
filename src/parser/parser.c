#include "../../include/minishell.h"

/* Goes through tokens and attributes the correct type for each. */
int	parser(t_tokens **tokens)
{
	t_tokens	*current;

	current = *tokens;
	while ((current))
	{
		if (!is_operator_token(current))
			if (!is_io_number_token(current))
				identify_token_type(current);
		current = current->next;
	}
	return (1);
}

/* Checks if current token is only numbers
 * and if previous and next token is a simple operator.*/
int	is_io_number_token(t_tokens *token)
{
	if (token->previous
		&& (token->previous->token[0] == '>'
			|| ((ft_strlen(token->previous->token) == 1
					&& token->previous->token[0] == '<'))))
	{
		if (is_only_digits(token->token))
		{
			token->token_type = IO_NUMBER;
			return (1);
		}
		else
		{
			token->token_type = FILE_NAME;
		}
	}
	return (0);
}

/* TODO: Remove before pushing, it's in the libft. Not in header. */
int	ft_isdigit2(int checkme)
{
	if (checkme >= 48 && checkme <= 57)
		return (1);
	else
		return (0);
}

/* Checks that all characters of the string are digits. */
int	is_only_digits(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (!ft_isdigit2(token[i]))
			return (0);
		i++;
	}
	return (1);
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
