#include "../../include/minishell.h"

/* Checks that tokens form a coherent command line. */
int	syntax_checker(t_master *master)
{
	t_tokens	*current;

	current = master->tokens;
	while (current)
	{
		if (current->token_type == PIPE_TOKEN
			&& (!current->previous
				|| !current->next
				|| current->previous->token_type == PIPE_TOKEN
				|| current->next->token_type == PIPE_TOKEN))
			return (err_msg("parsing: check the pipes", 0, master));
		else if (current->token_type == HERE_DOC
			&& (!current->next || current->next->token_type != DELIMITER))
			return (err_msg("parsing: HERE_DOC needs delimiter", 0, master));
		else if ((current->token_type == REDIRECT_TO
				|| current->token_type == REDIRECT_FROM
				|| current->token_type == APPEND)
			&& (!current->next
				|| (current->next->token_type != FILE_NAME)))
			return (err_msg("parsing: redirection needs file name",
					0, master));
		current = current->next;
	}
	return (1);
}
