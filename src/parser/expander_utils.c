/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:58:54 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 13:58:58 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Toggles quoting_status depending on current value. */
void	toggle_quoting(int *quoting_status)
{
	if (*quoting_status == 0)
		*quoting_status = 1;
	else
		*quoting_status = 0;
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

/* Logs all expansions in a token and inserts them one by one
 * starting from the end of the token. */
int	expand_token(t_tokens *token, t_master *master)
{
	t_tokens	*current;

	current = token;
	log_expansions(current->token, master);
	if (master->expansions)
	{
		if (!expand_line(&current->token, master))
			exit(err_msg("failed to expand token [expander()]",
					1, master));
		current->was_expanded = 1;
	}
	free_expansions(&master->expansions);
	return (1);
}

/* Expands all expansions, back to front. */
int	expand_line(char **line, t_master *master)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = master->expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, *line + exp->name_end + 1);
		if (!tmp_token)
			return (0);
		*(*line + exp->start) = '\0';
		new_token = str_join(*line, tmp_token);
		if (!new_token)
		{
			free(tmp_token);
			return (0);
		}
		free(tmp_token);
		tmp_token = *line;
		*line = new_token;
		free(tmp_token);
		exp = exp->next;
	}
	return (1);
}
