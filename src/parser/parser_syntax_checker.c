#include "../../include/minishell.h"

/* Checks that tokens form a coherent command line. */
// TODO Should I check the content of the command / filename names ?
// 		> Je crois paaaas.
// TODO Should I also check the FDs of the IO_NUMBERS ? > INT_MAX c'est ok ?
// 		Je dirais que oui puisqu'on peut set les FDs sur unlimited.
int	syntax_checker(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		if (current->token_type == PIPE_TOKEN
			&& (!current->previous
				|| !current->next
				|| current->previous->token_type == PIPE_TOKEN
				|| current->next->token_type == PIPE_TOKEN))
			return (err_msg("parse error: check the pipes", 0));
		else if (current->token_type == HERE_DOC
			&& (!current->next || current->next->token_type != DELIMITER))
			return (err_msg("parse error: HERE_DOC needs delimiter", 0));
		else if ((current->token_type == REDIRECT_TO
				|| current->token_type == REDIRECT_FROM
				|| current->token_type == APPEND)
			&& (!current->next
				|| (current->next->token_type != FILE_NAME
					&& current->next->token_type != IO_NUMBER)))
			return (err_msg("parse error: redirection needs file or fd", 0));
		current = current->next;
	}
	return (1);
}
