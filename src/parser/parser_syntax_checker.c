/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:20:46 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:20:48 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Checks that tokens form a coherent command line.
 * Had to be creative with return values so it would fit. */
int	syntax_checker(t_tokens *t, t_master *master, int err)
{
	while (t && !err)
	{
		if (t->token_type == PIPE_TOKEN
			&& (!t->previous || !t->next
				|| t->previous->token_type == PIPE_TOKEN
				|| t->next->token_type == PIPE_TOKEN))
			err = err_msg("parsing: check the pipes", 2, master);
		else if (t->token_type == HERE_DOC
			&& (!t->next || t->next->token_type != DELIMITER))
			err = err_msg("parsing: HERE_DOC needs delimiter", 2, master);
		else if ((t->token_type == REDIRECT_TO
				|| t->token_type == REDIRECT_FROM
				|| t->token_type == APPEND)
			&& (!t->next || (t->next->token_type != FILE_NAME)))
			err = err_msg("parsing: missing file name", 2, master);
		t = t->next;
	}
	if (err)
	{
		g_minishexit = err;
		return (0);
	}
	return (1);
}
