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

/* Checks that there is no quote without a matching quote. */
int	has_solitary_quote(char *token, t_master *master)
{
	int	i;
	int	matching_quote;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == SINGLE_QUOTE || token[i] == DOUBLE_QUOTE)
		{
			matching_quote = find_matching_quote(&token[i]);
			if (matching_quote)
				i += matching_quote + 1;
			else
				return (err_msg("open quote", 1, master));
		}
		else
			i++;
	}
	return (0);
}

/* When sent a $ char, returns the length of the name following that char.
 * Returns 0 if there is no name following it. */
int	expansion_name_len(char *expansion)
{
	int	i;

	expansion++;
	i = 0;
	if (expansion[i] == '?')
		return (1);
	while (ft_isalnum(expansion[i])
		|| expansion[i] == '_')
		i++;
	return (i);
}
