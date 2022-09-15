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

t_tokens	*split_expanded_token(t_tokens **token_ptr, t_master *master)
{
	int			i;
	char		**divided_token;
	t_master	tmp_master;
	t_tokens	*last_token;

	divided_token = ft_split_max((*token_ptr)->token, " 	\n");
	if (!divided_token)
		exit(err_msg("malloc fail [split_expanded_token()]", 1, master)
			&& free_all(master, 1));
	tmp_master.tokens = NULL;
	i = -1;
	while (divided_token[++i])
	{
		extract_token(&tmp_master, divided_token[i],
			&divided_token[i][ft_strlen(divided_token[i])]);
		last_token = get_last_token(tmp_master.tokens);
		last_token->was_isolated = 1;
		last_token->split_id = i;
		last_token->was_split = 1;
		last_token->token_had_quotes = (*token_ptr)->token_had_quotes;
		last_token->token_id = (*token_ptr)->token_id;
		last_token->token_type = (*token_ptr)->token_type;
	}
	free_divided_token(divided_token);
	return (tmp_master.tokens);
}

void	free_divided_token(char **divided_token)
{
	int	i;

	i = -1;
	while (divided_token[++i])
		free(divided_token[i]);
	free(divided_token);
}

void	tok_splitter(t_tokens *current, t_tokens **split_toks, t_master *master)
{
	*split_toks = split_expanded_token(&current, master);
	if (current->next)
	{
		current->next->previous = get_last_token(*split_toks);
		current->next->previous->next = current->next;
	}
	if (!current->previous)
	{
		free(current->token);
		free(current);
		master->tokens = *split_toks;
		current = master->tokens;
	}
	else
	{
		current->previous->next = *split_toks;
		(*split_toks)->previous = current->previous;
		free(current->token);
		free(current);
		current = *split_toks;
	}
}
