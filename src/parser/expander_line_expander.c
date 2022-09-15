/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_line_expander.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 10:23:09 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 10:23:16 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Expands all expansions, back to front. */
int	expand_line(char **line, t_master *master)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = master->expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, *line + exp->name_end + 1);
		if (!tmp_token)
			return (0);
		*(*line + exp->start) = '\0';
		new_token = str_join(*line, tmp_token);
		if (!new_token)
		{
			free(tmp_token);
			return (0);
		}
		free(tmp_token);
		tmp_token = *line;
		*line = new_token;
		free(tmp_token);
		exp = exp->next;
	}
	return (1);
}
