#include "../../include/tokenizer.h"

/* Takes a pointer to a string that starts with a quote character and returns
 * the position of the first occurrence of that same quote character. */
int	find_matching_quote(char *str)
{
	int		position;
	char	quote_char;

	quote_char = *str;
	position = 1;
	while (str[position])
	{
		if (str[position] == quote_char)
			return (position);
		position++;
	}
	return (-1);
}

/* Checks that the token being is no bigger than 2 characters, then checks if
 * both characters are the same chevron character. */
/*
int	can_form_operator(char *token_start, char *second_operator)
{
	char	*first_operator;

	first_operator = token_start;
	if ((second_operator - first_operator == 1)
		&& ((*first_operator == L_CHEVRON || *first_operator == R_CHEVRON)
			&& *first_operator == *second_operator))
		return (1);
	return (0);
}
*/

int	ft_isdigit(int checkme)
{
	if (checkme >= 48 && checkme <= 57)
		return (1);
	else
		return (0);
}

int	can_form_operator(char *token_start, char *current_char)
{
	int		token_len;
	int		i;

	token_len = current_char - token_start + 1;
	if (ft_isdigit(*current_char))
	{
		i = 0;
		while (i < token_len)
			if (!ft_isdigit(token_start[i++]))
				return (0);
		return (1);
	}
	if (*current_char == L_CHEVRON || *current_char == R_CHEVRON)
	{
		if (token_len == 1)
			return (1);
		if (ft_isdigit(*(current_char - 1)))
			return (1);
		if (*(current_char - 1) == *current_char)
			if (token_len == 2
				|| (token_len > 2 && ft_isdigit(*(current_char - 2))))
				return (1);
	}
	return (0);
}

/* Checks that the current position does not directly follow the latest
 * extracted token, that it is not the start of the line and whether
 * the previous character is actually part of a token or not. */
int	follows_open_token(t_tokenizer_helpers *t)
{
	if (t->last_token_end == t->position - 1)
		return (0);
	if (t->position == 0
		|| ((is_blank_char(t->line[t->position - 1]))
			|| (is_quote_character(t->line[t->position - 1])
				&& t->quote_match_found != -1)))
		return (0);
	return (1);
}

/* Checks that the position checked is not the start of the line and whether
 * the previous character is part of a word (meaning regular text) or not. */
int	follows_word(char *line, int position, int quote_match_found)
{
	if (position == 0)
		return (0);
	else if (((is_blank_char(line[position - 1]))
			|| is_operator(line[position - 1])
			|| (is_quote_character(line[position - 1])
				&& quote_match_found != -1)))
		return (0);
	return (1);
}
