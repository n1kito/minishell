#include "../../include/parser.h"

void	parser(t_tokens **tokens)
{
		t_tokens	*current;

		current = *tokens;
		while ((current))
		{
				if (!is_operator_token(current))
						if (!is_io_number_token(current))
								is_simple_token(current);
				current = current->next;
		}
}

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
						token->token_type = PIPE;
		}
		return (1);
}
