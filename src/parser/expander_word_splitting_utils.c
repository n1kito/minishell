#include "minishell.h"

t_tokens	*get_next_unsplitted_token(t_tokens *current)
{
	current = current->next;
	while (current)
	{
		if (current->word_splitted == 0)
			return (current);
		else
			current = current->next;
	}
	return (current);
}

int	get_next_non_blank_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_blank_char(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	set_tokens_as_words(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		current->token_type = WORD;
		current->was_expanded = 1;
		current = current->next;
	}
}
