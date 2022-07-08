#include "../../include/tokenizer.h"

/*

The tokenizer() function strictly follows the shell guidelines.
See README for more information.

*/

int	is_operator(char c)
{
	if (c && (c == '<' || c == '>' || c == '|'))
		return (1);
	return (0);
}

int	can_form_operator(char *token_start, char *second_token)
{
	char	*first_token;

	first_token = token_start;
	if ((second_token - first_token == 1)
		&& ((*first_token == '>' && *second_token == '>')
			|| (*first_token == '<' && *second_token == '<')))
		return (1);
	return (0);
}

int	is_quote_character(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_blank_character(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}

int	is_part_of_token(char *ptr)
{
	if ((is_blank_character(*ptr) || is_operator(*ptr))
		|| is_quote_character(*ptr))
		return (0);
	return (1);
}

int	is_part_of_word(char *ptr)
{
	if ((is_blank_character(*ptr)))
		return (0);
	return (1);
}

int	get_matching_quote_position(char *str)
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
	int		current_char;
	int		matching_quote_position;

	token_start = 0;
	current_char = 0;
	matching_quote_position = 0;
	while (current_char <= ft_strlen(line))
	{
		// 1
		// If the end of input is recognized, the current token (if any) shall
		// be delimited.
		if (line[current_char] == '\0')
		{
			ONE
			if (token_start != current_char && (is_part_of_word(&line[current_char - 1]) ||
					is_operator(line[current_char - 1])))
			add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			current_char++;
		}
		// 2
		// If the previous character was used as part of an operator and the
		// current character is not quoted and can be used with the previous
		// characters to form an operator, it shall be used as part of that (operator) token.
		else if (is_operator(line[current_char - 1])
			&& can_form_operator(&line[token_start], &line[current_char]))
		{
			TWO
			current_char++;
		}
		// 3
		// If the previous character was used as part of an operator and the
		// current character cannot be used with the previous characters to form
		// an operator, the operator containing the previous character shall be delimited.
		else if (is_operator(line[current_char - 1])
			&& !can_form_operator(&line[token_start], &line[current_char]))
		{
			THREE
			add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			token_start = current_char;
			current_char++;
		}
		// 4
		// If the current character is single-quote, or double-quote
		// and it is not quoted, it shall affect quoting for subsequent characters
		// up to the end of the quoted text.
		else if (is_quote_character(line[current_char]))
		{
			FOUR
			matching_quote_position = get_matching_quote_position(&line[current_char]);
			if (matching_quote_position > 0)
			{
				if (is_part_of_token(&line[current_char - 1]) && !is_quote_character(line[current_char - 1]))
				{
					add_token_node(tokens, &line[token_start], &line[current_char - 1]);
					token_start = current_char;
				}
				if (matching_quote_position == 1)
				{
					current_char += 2;
					token_start = current_char;
				}
				else
				{
					current_char += matching_quote_position;
					// uncomment to not include quotes in token. I think we actually need them.
//					token_start++;
//					add_token_node(tokens, &line[token_start], &line[current_char - 1]);
					add_token_node(tokens, &line[token_start], &line[current_char]);
					current_char++;
					token_start = current_char;
				}
			}
			else
				current_char++;
		}
		// 5
		// If the current character is an unquoted $,
		// the shell shall identify the start of any candidates for expansion.
		else if (line[current_char] == '$')
		{
			FIVE
			if (current_char
				&& (is_part_of_token(&line[current_char - 1]) || (!is_blank_character(line[current_char - 1]) && matching_quote_position == -1))) // TODO je dois fix la fonction is_token() en fait pour inclure le fait que des fois un quote peut etre token s'il n'a pas de matching.
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			token_start = current_char;
			current_char++;
		}
		// 6
		// If the current character is not quoted and can be used as the first
		// character of a new operator, the current token (if any) shall be
		// delimited. The current character shall be used as the beginning of
		// the next (operator) token.
		else if (is_operator(line[current_char]))
		{
			SIX
			if (current_char && is_part_of_token(&line[current_char - 1])) // checks that we're not a the start of a line and that the previous char is not a blank
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			token_start = current_char;
			current_char++;
		}
		// 7
		// If the current character is an unquoted `<blank>`, any token containing
		// the previous character is delimited and the current character shall be discarded.
		else if (is_blank_character(line[current_char]) /*&& !is_quote_character(line[current_char - 1])*/)
		{
			SEVEN
			if (current_char && !is_blank_character(line[current_char - 1])
				&& (is_part_of_token(&line[current_char - 1])
				|| (is_quote_character(line[current_char - 1])
				&& matching_quote_position == -1)))
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			current_char++;
			token_start = current_char;
		}
		// 8
		// If the previous character was part of a word, the current character
		// shall be appended to that word.
		else if (current_char && (is_part_of_token(&line[current_char - 1]) || matching_quote_position == -1))
		{
			EIGHT
			current_char++;
		}
		// 10
		// The current character is used as the start of a new word.
		else
		{
			TEN
			if (!is_quote_character(line[current_char - 1]))
				token_start = current_char;
			current_char++;
		}
	}
}
