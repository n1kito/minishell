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
	/* I ended up not identifying COMMAND_NAMES separately, because it
	 * makes stuff complicated with invisible tokens.
	else if (current->previous == NULL
		|| (!found_command_in_current_segment(token)
			&& (current->previous->token_type == PIPE_TOKEN
				|| current->previous->token_type == IO_NUMBER
				|| current->previous->token_type == DELIMITER
				|| current->previous->token_type == FILE_NAME)))
		current->token_type = COMMAND_NAME;
	*/
	else if (current->token_type == TOKEN)
		current->token_type = WORD;
}
