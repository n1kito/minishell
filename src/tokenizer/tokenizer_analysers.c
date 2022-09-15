/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_analysers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjallada <mjallada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:21:04 by mjallada          #+#    #+#             */
/*   Updated: 2022/09/15 14:21:05 by mjallada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if character is a chevron or a pipe. */
int	is_operator(char c)
{
	if (c && (c == L_CHEVRON || c == R_CHEVRON || c == PIPE))
		return (1);
	return (0);
}

/* Checks if character is a single or double quote. */
int	is_quote_character(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}

/* Checks if character is a space or a tab. */
int	is_blank_char(char c)
{
	if (c == SPACE || c == TAB)
		return (1);
	return (0);
}
