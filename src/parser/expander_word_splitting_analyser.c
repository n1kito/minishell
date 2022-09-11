#include "minishell.h"

int	token_has_unquoted_blanks(t_tokens *token)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if (token->token[i] == DOUBLE_QUOTE)
			i += find_matching_quote(&token->token[i]) + 1;
		else if (is_blank_char(token->token[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

int	has_single_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
			i += find_matching_quote(&str[i]) + 1;
		if (str[i] == SINGLE_QUOTE && find_matching_quote(&str[i]))
			return (1);
		else
			i++;
	}
	return (0);
}
