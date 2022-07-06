#include "../../include/tokenizer.h"

/*

The tokenizer() function strictly follows the shell guidelines.
See README for more information.

*/

t_tokens	*get_last_token(t_tokens *tokens_list)
{
	t_tokens	*current;

	current = tokens_list;
	while (current && current->next)
		current = current->next;
	return (current);
}

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
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE) // Backslash character is not included in the subject
		return (1);
	return (0);
}

int	is_blank_character(char c)
{
	if (c == ' ' || c == '	') // TODO check for other possible blanks
		return (1);
	return (0);
}

void	add_token_node(t_tokens **tokens, char *token_start, char *token_end)
{
	int			token_len;
	t_tokens	*new_token;
	int			i;

	PLUS
	token_len = (token_end - token_start) + 1;
	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->token = malloc(sizeof(char) * (token_len + 1));
	if (!new_token->token)
		return ;
	i = -1;
	while (++i < token_len)
		new_token->token[i] = token_start[i];
	new_token->token[i] = '\0';
	new_token->next = NULL;
	if ((*tokens) == NULL)
		*tokens = new_token;
	else
		get_last_token(*tokens)->next = new_token;
}

int	is_part_of_token(char *ptr)
{
	if ((is_blank_character(*ptr) || is_operator(*ptr)))
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
//	int		quoting;

	token_start = 0;
	current_char = 0;
//	quoting = 0;
	while (current_char <= ft_strlen(line))
	{
		// 1
		// If the end of input is recognized, the current token (if any) shall
		// be delimited.
		if (line[current_char] == '\0')
		{
			ONE
//			if (is_part_of_token(&line[current_char - 1]))
			if (token_start != current_char && is_part_of_token(&line[current_char - 1]))
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			break ;
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
		else if (is_operator(line[current_char - 1]) && !can_form_operator(&line[token_start], &line[current_char]))
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
			current_char += get_matching_quote_position(&line[current_char]);
			if (current_char == -1)
			{
				printf("\033[31;5mError\033[0;39m\n> Quotes not properly closed.\n");
				exit (-1);
			}
			token_start++;
			add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			current_char++;
			token_start = current_char;
		}
		// 5
		// If the current character is an unquoted $ or ``` (accent grave),
		// the shell shall identify the start of any candidates for expansion.
		//
		// 6
		// If the current character is not quoted and can be used as the first
		// character of a new operator, the current token (if any) shall be
		// delimited. The current character shall be used as the beginning of
		// the next (operator) token.
		else if (is_operator(line[current_char]))
		{
			SIX
			if (current_char && is_part_of_token(&line[current_char - 1])) // checks that we're not a the start of a line and that the previous char is not a blank
			{
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
				token_start = current_char;
			}
			token_start = current_char;
			current_char++;
		}
		// 7
		// If the current character is an unquoted `<blank>`, any token containing
		// the previous character is delimited and the current character shall be discarded.
		else if (is_blank_character(line[current_char]) && !is_quote_character(line[current_char - 1]))
		{
			SEVEN
			if (current_char && is_part_of_token(&line[current_char - 1]))
				add_token_node(tokens, &line[token_start], &line[current_char - 1]);
			token_start = current_char + 1;
			current_char = token_start;
		}
		// 8
		// If the previous character was part of a word, the current character
		// shall be appended to that word.
		else if (current_char && is_part_of_token(&line[current_char - 1]))
		{
			EIGHT
			current_char++;
		}
		// 9
		// I we don't handle this rule
		//
		// 10
		// The current character is used as the start of a new word.
		else
		{
			TEN
			token_start = current_char;
			current_char++;
		}
	}
}
