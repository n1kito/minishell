#include "../../include/minishell.h"

char	*ft_strchr(char *str, int c)
{
	int	index;

	index = -1;
	while (str && str[++index])
		if (str[index] == c)
			return (str + index);
	return (NULL);
}

/* Checks that the string before the '=' sign contains a valid name. */
// TODO temporarily code the isdigit and isalpha functions since I'm not using libft right now. Or just include the libft once and for all.
int	has_valid_assignment_name(t_tokens *token_ptr)
{
	int		i;
	char	*token;
	char	*end_of_name;
	
	token = token_ptr->token;
	if (token[0] == '=') || ft_isdigit(token[0]))
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

/* Receives token and follows shell grammar rules to assign the correct
 * token type */
void	identify_token_type(t_tokens *token)
{
	t_tokens	*current;	

	current = token;
	if (current->previous == NULL)
	{
		if (ft_strchr(current->token, '='))
			if (has_valid_assignment_name(current))
				current->token_type = ASSIGNMENT_WORD;
		else
			current->token_type = WORD;
	}
}
