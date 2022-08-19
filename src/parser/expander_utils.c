#include "../../include/minishell.h"

/* Joins two strings of characters. Will still work if either is NULL. */
char	*str_join(char *token1, char *token2)
{
	char	*new_token;
	int		i;
	int		j;

	new_token = malloc(sizeof(char)
			* ((ft_strlen(token1) + ft_strlen(token2)) + 1));
	if (!new_token)
		return (NULL);
	i = 0;
	while (token1 && token1[i])
	{
		new_token[i] = token1[i];
		i++;
	}
	j = 0;
	while (token2 && token2[j])
		new_token[i++] = token2[j++];
	new_token[i] = '\0';
	return (new_token);
}

/* When sent a $ char, returns the length of the name following that char.
 * Returns 0 if there is no name following it. */
int	expansion_name_len(char *expansion)
{
	int	i;

	expansion++;
	i = 0;
	while (expansion[i]
		&& !is_blank_char(expansion[i])
		&& !is_quote_character(expansion[i])
		&& expansion[i] != '$')
			i++;
	return (i);
}

/* Toggles quoting_status depending on current value. */
void	toggle_quoting(int *quoting_status)
{
	if (*quoting_status == 0)
		*quoting_status = 1;
	else
		*quoting_status = 0;
}

/* Counts how many expansions are logged in the expand linked list. */
int	count_expands(t_expand *expansions)
{
	int			count;
	t_expand	*current;

	current = expansions;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* Free the structure used to log expansions. */
int	free_expansions(t_expand **expansions)
{
	t_expand		*current;
	t_expand		*next;

	current = *expansions;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*expansions = NULL;
	return (1);
}
