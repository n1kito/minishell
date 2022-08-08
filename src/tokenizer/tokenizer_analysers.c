#include "../../include/tokenizer.h"

/* Checks if character is a chevron or a pipe. */
int	is_operator(char c)
{
	if (c && (c == L_CHEVRON || c == R_CHEVRON || c == PIPE))
		return (1);
//	else if (c >= 48 && c <= 57) // replace with ft_isdigit
//		return (1);
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
