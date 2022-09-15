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
	expanded_token_split_loop(master, &split_tokens);
	merge_back_loop(master);
	check_for_invisible_tokens(master->tokens);
}
