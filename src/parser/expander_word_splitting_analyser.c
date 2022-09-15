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
