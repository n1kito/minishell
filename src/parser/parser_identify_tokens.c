#include "../../include/minishell.h"

int	found_command_in_current_segment(t_tokens *token)
{
	t_tokens	*current;

	current = token->previous;
	while (current && current->token_type != PIPE_TOKEN)
	{
		if (current->token_type == COMMAND_NAME)
			return (1);
		current = current->previous;
	}
	return (0);
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
