#include "../../include/tokenizer.h"

/*

The tokenizer() function strictly follows the shell guidelines.
See README for more information.

*/

int	is_operator(char c)
{
	if (c && (c == L_CHEVRON || c == R_CHEVRON || c == PIPE))
		return (1);
	return (0);
}

int	is_quote_character(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	is_blank_char(char c)
{
	if (c == SPACE || c == TAB)
		return (1);
	return (0);
}

/* Checks that the token being is no bigger than 2 characters, then checks if
 * both characters are the same chevron character. */
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

/* Checks that the position checked is not the start of the string and whether
 * the previous character is part of a token */
int	follows_token(char *line, int position, int quote_match_found)
{
	if (position == 0
		|| ((is_blank_char(line[position - 1]))
			|| (is_quote_character(line[position - 1]) && quote_match_found != -1)))
		return (0);
	return (1);
}

/* Checks that the position checked is not the start of the string and whether
 * the previous character is part of a word (meaning regular text) */
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

void	tokenizer(char *line, t_tokens **tokens)
{
	int		token_start;
	int		position;
	int		quote_match_found;

	token_start = 0;
	position = 0;
	quote_match_found = 0;
	while (position <= ft_strlen(line))
	{
		// 1
		// If the end of input is recognized, the current token (if any) shall
		// be delimited.
		if (line[position] == '\0')
		{
			ONE
			if (follows_token(line, position, quote_match_found))
				extract_token(tokens, &line[token_start], &line[position - 1]);
			position++;
		}
		// 2
		// If the previous character was used as part of an operator and the
		// current character is not quoted and can be used with the previous
		// characters to form an operator, it shall be used as part of that (operator) token.
		else if (is_operator(line[position - 1])
			&& can_form_operator(&line[token_start], &line[position]))
		{
			TWO
			position++;
		}
		// 3
		// If the previous character was used as part of an operator and the
		// current character cannot be used with the previous characters to form
		// an operator, the operator containing the previous character shall be delimited.
		else if (is_operator(line[position - 1])
			&& !can_form_operator(&line[token_start], &line[position]))
		{
			THREE
			extract_token(tokens, &line[token_start], &line[position - 1]);
			token_start = position++;
		}
		// 4
		// If the current character is single-quote, or double-quote
		// and it is not quoted, it shall affect quoting for subsequent characters
		// up to the end of the quoted text.
		else if (is_quote_character(line[position]))
		{
			FOUR
			quote_match_found = find_matching_quote(&line[position]);
			if (quote_match_found > 0)
			{
				if (follows_token(line, position, quote_match_found))
				{
					extract_token(tokens, &line[token_start], &line[position - 1]);
					token_start = position;
				}
				if (quote_match_found == 1)
				{
					position += 2;
					token_start = position;
				}
				else
				{
					position += quote_match_found;
					extract_token(tokens, &line[token_start], &line[position]);
					position++;
					token_start = position;
				}
			}
			else
				position++;
		}
		// 5
		// If the current character is an unquoted $,
		// the shell shall identify the start of any candidates for expansion.
		else if (line[position] == '$')
		{
			FIVE
			if (follows_token(line, position, quote_match_found))
				extract_token(tokens, &line[token_start], &line[position - 1]);
			token_start = position;
			position++;
		}
		// 6
		// If the current character is not quoted and can be used as the first
		// character of a new operator, the current token (if any) shall be
		// delimited. The current character shall be used as the beginning of
		// the next (operator) token.
		else if (is_operator(line[position]))
		{
			SIX
			if (follows_token(line, position, quote_match_found))
				extract_token(tokens, &line[token_start], &line[position - 1]);
			token_start = position;
			position++;
		}
		// 7
		// If the current character is an unquoted `<blank>`, any token containing
		// the previous character is delimited and the current character shall be discarded.
		else if (is_blank_char(line[position]))
		{
			SEVEN
			if (follows_token(line, position, quote_match_found))
				extract_token(tokens, &line[token_start], &line[position - 1]);
			position++;
			token_start = position;
		}
		// 8
		// If the previous character was part of a word, the current character
		// shall be appended to that word.
		else if (follows_word(line, position, quote_match_found))
		{
			EIGHT
			position++;
		}
		// 10
		// The current character is used as the start of a new word.
		else
		{
			TEN
//			if (!is_quote_character(line[position - 1]))
			token_start = position;
			position++;
		}
	}
}
