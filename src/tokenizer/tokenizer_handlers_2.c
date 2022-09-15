/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:21:43 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:21:44 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Called when '$' character is found.*/
void	start_expansion_token(t_tokenizer_helpers *t)
{
	t->position++;
}

/* Called on operator character. Extracts preceding token if necessary. */
void	start_operator_token(t_tokenizer_helpers *t, t_master *master)
{
	if (follows_open_token(t))
	{
		extract_token(master, &t->line[t->token_start],
			&t->line[t->position - 1]);
		t->last_token_end = t->position - 1;
	}
	t->token_start = t->position;
	t->position++;
}

/* Called when the current operator token can no longer be appended to. */
void	close_operator_token(t_tokenizer_helpers *t, t_master *master)
{
	extract_token(master,
		&t->line[t->token_start], &t->line[t->position - 1]);
	if (t->position)
		t->last_token_end = t->position - 1;
	t->token_start = t->position;
}
