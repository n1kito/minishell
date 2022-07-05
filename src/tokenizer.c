#include <stdio.h>
#include <stdlib.h>

// Blank Characters
#define SPACE 32
#define TAB 9
// Operator Characters
#define PIPE 124
#define LEFT_CHEVRON 60
#define RIGHT_CHEVRON 62
// Quote Characters
#define BACKSLASH 92
#define SINGLE_QUOTE 39
#define DOUBLE_QUOTE 34

/*

The tokenizer() function follows the shell guidelines.
See README for more information.

*/

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

void	print_tokens(t_tokens *tokens)
{
	t_tokens	*current;

	printf("\033[0;35m[\033[0m");
	current = tokens;
	while (current)
	{
		printf("%s", current->token);
		if (current->next)
			printf("\033[0;35m|\033[0m");
		current = current->next;
	}
	printf("\033[0;35m]\033[0m\n");
}

t_tokens	*get_last_token(t_tokens *tokens_list)
{
	t_tokens	*current;

	current = tokens_list;
	while (current && current->next)
		current = current->next;
	return (current);
}

int ft_strlen(char *string)
{
	int i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

int	is_operator(char c)
{
	if (c && (c == '<' || c == '>' || c == '|'))
//	if (c && (c == LEFT_CHEVRON || c == RIGHT_CHEVRON || c == PIPE))
		return (1);
	return (0);
}

int	can_form_operator(char *token_start, char *second_token)
{
	char *first_token;

	first_token = token_start;
//	printf("operator len: %ld\n", second_token - first_token);
	if ((second_token - first_token == 1)
		&& ((*first_token == '>' && *second_token == '>')
		|| (*first_token == '<' && *second_token == '<')))
		return (1);
	return (0);
}

int	is_quote_character(char c)
{
	if (c == BACKSLASH || c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	is_blank_character(char c)
{
	if (c == ' ' || c == '	') // TODO check for other possible blanks
		return (1);
	return (0);
}

void	add_token_node(t_tokens **tokens, char *token_start, int token_len)
{
	t_tokens	*new_token;
	int			i;

	if (token_len == 0)
		token_len++;
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

int extract = 0;

void	extract_node(t_tokens **tokens, char *token_ptr, char *token_start, char *token_end)
{
//	printf("extract #%d\n", ++extract);
//	printf("token len: %d\n", (int)(token_end - token_start));
	if (!is_blank_character(*token_start) || !is_blank_character(*token_end))
		add_token_node(tokens, token_ptr, (int)(token_end - token_start + 1));
//	printf("extracted \"%s\"\n", get_last_token(*tokens)->token);
	printf("+ ");
}

int	is_part_of_token(char *ptr)
{
	if (is_blank_character(*ptr) || is_operator(*ptr))
		return (0);
	return (1);
}

void	tokenizer(char *line, t_tokens **tokens)
{
	int	token_start;
	int	current_char;
//	int quoting;

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
			printf("[Rule 1] ");
			extract_node(tokens, &line[token_start], &line[token_start], &line[current_char - 1]);
			break ;
		}
		// 2
		// If the previous character was used as part of an operator and the
		// current character is not quoted and can be used with the previous
		// characters to form an operator, it shall be used as part of that (operator) token.
		else if (is_operator(line[current_char - 1]) && can_form_operator(&line[token_start], &line[current_char]))
		{
			printf("[Rule 2] ");
//			extract_node(tokens, &line[token_start], &line[token_start], &line[current_char]);
//			token_start = current_char + 1;
//			current_char = token_start;
			current_char++;
			// I could replace this with token_start = ++current_char;
		}
		// 3
		// If the previous character was used as part of an operator and the
		// current character cannot be used with the previous characters to form
		// an operator, the operator containing the previous character shall be delimited.
		else if (is_operator(line[current_char - 1]) && !can_form_operator(&line[token_start], &line[current_char]))
		{
			printf("[Rule 3] ");
			extract_node(tokens, &line[token_start], &line[token_start], &line[current_char] - 1);
			token_start = current_char;
			current_char++;
		}
		// 4
		//
		// 5
		//
		// 6
		// If the current character is not quoted and can be used as the first
		// character of a new operator, the current token (if any) shall be
		// delimited. The current character shall be used as the beginning of
		// the next (operator) token.
		else if (is_operator(line[current_char]))
		{
			printf("[Rule 6] ");
			if (current_char && is_part_of_token(&line[current_char - 1])) // checks that we're not a the start of a line and that the previous char is not a blank
			{
				extract_node(tokens, &line[token_start], &line[token_start], &line[current_char - 1]);
				token_start = current_char;
			}
			current_char++;
		}
		// 7
		// If the current character is an unquoted `<blank>`, any token containing
		// the previous character is delimited and the current character shall be discarded.
		else if (is_blank_character(line[current_char]))
		{
			printf("[Rule 7] ");
			if (current_char && is_part_of_token(&line[current_char - 1]))
				extract_node(tokens, &line[token_start], &line[token_start], &line[current_char] - 1);
			token_start = current_char + 1;
			current_char = token_start;
			// I could replace this with token_start = ++current_char;
		}
		// 8
		// If the previous character was part of a word, the current character
		// shall be appended to that word.
		else if (is_part_of_token(&line[current_char - 1]))
		{
			printf("[Rule 8] ");
			current_char++;
		}
		// 9
		// I we don't handle this rule
		//
		// 10
		// The current character is used as the start of a new word.
		else
		{
			printf("[Rule 10] ");
			token_start = current_char;
			current_char++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_tokens	*tokens;

	tokens = NULL;
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		printf(" %s\n", argv[1]);
		tokenizer(argv[1], &tokens);
		printf("\n");
		print_tokens(tokens);
	}
	return (0);
}

// TODO
// Fix this case, why is it adding a space after the first token ????
// > >>|aabcd +++>>>>>>>|
// [>| |>>|||aabcd|+++|>>|>>|>>|>||]


// tests
// ./tokenizer "a"
// ./tokenizer "a b c d e f gh ij kl mnop ejrkewjrkewjrkwejrwejkrew"
// operator tests
// a b c d e>f|>>g||h<<i<<<
// [a|b|c|d|e|>|f|||>>|g|||||h|<<|i|<<|<]
//
//
// quotes tests
//
