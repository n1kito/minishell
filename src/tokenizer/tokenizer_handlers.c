/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:22:17 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:22:18 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Called when EOL character is found in line. */
void	handle_end_of_line(t_tokenizer_helpers *t, t_master	*master)
{
	if (follows_open_token(t))
	{
		extract_token(master, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->position++;
}

/* Called when quote character is found.
 * Will look for matching quote char and extend token to it if found.
 * Else it will just move forward one char.*/
void	handle_quotes(t_tokenizer_helpers *t)
{
	t->quote_match_found = find_matching_quote(&t->line[t->position]);
	if (t->quote_match_found)
		t->position += t->quote_match_found;
	t->position++;
}

/* Called when blank char is found. Extracts preceding token if necessary. */
void	handle_blank_char(t_tokenizer_helpers *t, t_master *master)
{
	if (follows_open_token(t))
	{
		extract_token(master, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->position++;
	t->token_start = t->position;
}
