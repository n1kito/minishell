/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word_splitting_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:15:37 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:30:17 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*get_next_unsplitted_token(t_tokens *current)
{
	current = current->next;
	while (current)
	{
		if (current->word_splitted == 0)
			return (current);
		else
			current = current->next;
	}
	return (current);
}

int	get_next_non_blank_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_blank_char(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	set_tokens_as_words(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		current->token_type = WORD;
		current->was_expanded = 1;
		current = current->next;
	}
}

int	go_to_end_of_expand_name(t_tokens *current_ptr, int i)
{
	if (!ft_isalpha(current_ptr->token[i + 1])
		&& current_ptr->token[i + 1] != '_'
		&& current_ptr->token[i + 1] != '?')
		return (i + 1);
	i++;
	while (current_ptr->token[i]
		&& (ft_isalnum(current_ptr->token[i])
			|| current_ptr->token[i] == '_'
			|| current_ptr->token[i] == '?'))
		i++;
	return (i);
}

void	free_split_tokens(char **divided_token)
{
	int	i;

	i = 0;
	while (divided_token[i])
		free(divided_token[i++]);
	free(divided_token);
}
