/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:17:36 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:17:38 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
void	expander(t_master *master)
{
	t_tokens	*split_tokens;

	split_tokens = NULL;
	add_token_ids(master->tokens);
	isolate_loop(master);
	check_for_quotes(master->tokens);
	expand_loop(master);
	quotes_removal_loop(master);
	expanded_token_split_loop(master, &split_tokens); // ca merde ici
	merge_back_loop(master);
	check_for_invisible_tokens(master->tokens);
}
