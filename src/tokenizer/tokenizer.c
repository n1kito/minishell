/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:15:59 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:16:04 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* The tokenizer() function strictly follows the bash guidelines.
See README for more information. */
void	tokenizer(char *line, t_master *master, t_tokenizer_helpers *t)
{
	while (t->position <= (int)ft_strlen(line))
	{
		if (line[t->position] == '\0')
			handle_end_of_line(t, master);
		else if (can_form_operator(&line[t->token_start], &line[t->position]))
			t->position++;
		else if (t->position && is_operator(line[t->position - 1])
			&& !can_form_operator(&line[t->token_start], &line[t->position])
			&& t->last_token_end != t->position - 1)
			close_operator_token(t, master);
		else if (is_quote_character(line[t->position]))
			handle_quotes(t);
		else if (line[t->position] == '$')
			start_expansion_token(t);
		else if (is_operator(line[t->position]))
			start_operator_token(t, master);
		else if (is_blank_char(line[t->position]))
			handle_blank_char(t, master);
		else if (follows_word(line, t->position))
			t->position++;
		else
			t->token_start = t->position++;
	}
}
