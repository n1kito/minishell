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

void	add_token_ids(t_tokens *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token->token_id = i++;
		token->split_id = 0;
		token = token->next;
	}
}

void	check_for_quotes(t_tokens *tokens)
{
	int			i;
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		i = 0;
		while (current->token[i])
		{
			if ((current->token[i] == SINGLE_QUOTE
					|| current->token[i] == DOUBLE_QUOTE)
				&& find_matching_quote(current->token + i))
				current->token_had_quotes = 1;
			i++;
		}
		current = current->next;
	}
}

int	token_has_blank(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
		if (is_blank_char(token[i]))
			return (1);
	return (0);
}

int	is_only_blanks(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' '
			&& str[i] != '	'
			&& str[i] != '\n')
			return (0);
	}
	return (1);
}
