/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:21:07 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:21:25 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If the token passed as parameter is of type WORD, is empty
 * and did not initially have empty quotes in it, it will be 
 * typed as INVISIBLE. */
void	check_for_invisible_tokens(t_tokens *token)
{
	t_tokens	*current;

	current = token;
	while (current)
	{
		if ((int)ft_strlen(current->token) == 0
			&& !current->token_had_quotes)
				current->token_type = INVISIBLE;
		current = current->next;
	}
}

/* Goes through token list and adds an ID to each one. */
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
