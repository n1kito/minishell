#include "../../include/minishell.h"

/*
char	*ft_strchr(char *str, int c)
{
	int	index;

	index = -1;
	while (str && str[++index])
		if (str[index] == c)
			return (str + index);
	return (NULL);
}

int	ft_isalpha(int tocheck)
{
	if (tocheck >= 65 && tocheck <= 90)
		return (1);
	if (tocheck >= 97 && tocheck <= 122)
		return (1);
	else
		return (0);
}

// I don't need this one anymore because we don't handle this case.
// Checks that the string before the '=' sign contains a valid name.
// TODO temporarily code the isdigit and isalpha functions since I'm not using libft right now. Or just include the libft once and for all.
int	has_valid_assignment_name(t_tokens *token_ptr)
{
	int		i;
	char	*token;
	
	token = token_ptr->token;
	if ((token[0] == '=') || ft_isdigit(token[0]))
		return (0);
	i = 0;
	while (token[i])
	{
		if (!ft_isdigit(token[i])
			|| !ft_isalpha(token[i])
			|| token[i] == '_')
			return (0);
		i++;
	}
	token_ptr->assignment_name_len = (int)(ft_strchr(token, '=') - token);	
	return (1);
}
*/

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

/* Receives token and follows shell grammar rules to assign the correct
 * token type. */
// 1. [COMMAND_NAME]
// Only called by other rules. First checks if it is a [WORD]. Then I think if it is the first [WORD] in the "pipe section" and respects naming rules, it should be typed [COMMAND_NAME].
// 2. [REDIRECTION TO or FROM FILENAME]
// 
void	identify_token_type(t_tokens *token)
{
	t_tokens	*current;	

	current = token;
	if (current->previous && current->previous->token_type == HERE_DOC)
		current->token_type = DELIMITER;
	else if (current->previous == NULL
			|| (!found_command_in_current_segment(token)
				&& (current->previous->token_type == PIPE_TOKEN
					|| current->previous->token_type == IO_NUMBER
					|| current->previous->token_type == DELIMITER
					|| current->previous->token_type == FILE_NAME)))
		current->token_type = COMMAND_NAME;
	else if (current->token_type == TOKEN)
		current->token_type = WORD;
}
