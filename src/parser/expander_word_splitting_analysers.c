/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_splitting_analysers.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:15:50 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:20:19 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if token has blank characters. */
int	token_has_blank(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
		if (token[i] == ' '
			&& token[i] == '	'
			&& token[i] == '\n')
			return (1);
	return (0);
}

/* Checks if token only contains blank characters */
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

int	follows_unquoted_expand(t_tokens *token_ptr, int i)
{
	if (i && is_unquoted_expand(token_ptr, 0))
		return (1);
	return (0);
}

int	is_unquoted_expand(t_tokens *token_ptr, int i)
{
	if (token_ptr->token[i] == '$')
	{
		i++;
		if (ft_isalpha(token_ptr->token[i])
			|| token_ptr->token[i] == '_'
			|| token_ptr->token[i] == '?')
			return (1);
	}
	return (0);
}
