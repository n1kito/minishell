#include "../../include/minishell.h"

int		find_quote_char(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == SINGLE_QUOTE
				|| token[i] == DOUBLE_QUOTE)
			return (i);
		i++;
	}
	return (0);
}

void	deal_with_the_quotes(t_tokens **token)
{
	// TODO Continue coding here
}

void	quote_expander(t_tokens	**tokens, t_env *env)
{
	t_tokens	*current;
	int			quote_found;

	current = *tokens;
	while (current)	
	{
		quote_found = find_quote_char(current->token);
		if (quote_found
			&& find_matching_quote(&current->token[quote_found]))
			deal_with_the_quotes(&current);
		current = current->next;
	}
}

