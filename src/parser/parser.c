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

void	classify_as_simple_token(t_tokens *token)
	{
		if (token)
			token->token_type = 0;
	}

int	is_io_number_token(t_tokens *token)
{
	if (is_only_digits(token->token))
	{
		if ((ft_strlen(token->previous->token) == 1
				&& ((token->previous->token[0] == '<')
					|| token->previous->token[0] == '>'))  
			|| (ft_strlen(token->next->token) == 1
				&& ((token->next->token[0] == '<')
					|| token->next->token[0] == '>')))
			{
				token->token_type = IO_NUMBER;
				return (1);
			}
	}
	return (0);
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

void	print_parsed_tokens(t_tokens *tokens)
{
		t_tokens	*current;

		current = tokens;
		COLOR_CROCHET_START
		while (current)
		{
			if (current->token_type = 1)
				printf("WORD");
			else if (current->token_type = 2)
				printf("ASSIGNMENT_WORD");
			else if (current->token_type = 3)
				printf("NAME");
			else if (current->token_type = 4)
				printf("IO_NUMBER");
			else if (current->token_type = 5)
				printf("REDIRECT_FROM");
			else if (current->token_type = 6)
				printf("REDIRECT_TO");
			else if (current->token_type = 7)
				printf("HERE_DOC");
			else if (current->token_type = 8)
				printf("PIPE");
			else
				printf("UNKNOWN");
			if (current->next)
				PIPE_PRINT
			current = current->next;
		}
		COLOR_CROCHET_END
}
