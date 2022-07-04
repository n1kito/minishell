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

void	add_token_node(t_tokens **tokens, char *token_start, int token_len)
{
	t_tokens	*new_token;
	int			i;

	if (token_len == 0)
//		return ;
		token_len = 1;
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

int	can_form_operator(char *second_token)
{
	char *first_token;

	first_token = second_token - 1;
	if (*first_token == '>' && *second_token == '>')
		return (1);
	//TODO – Add other operators conditions
}

int	is_quote_character(char c)
{
	if (c == BACKSLASH || c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (1);
	return (0);
}

void	extract_node(t_tokens **tokens, char *token_ptr, int *token_start, int *token_end)
{
	add_token_node(tokens, token_ptr, (*token_end - *token_start));
//	*token_start = *token_end + 1;
//	*token_end = *token_start;
//	*token_end += 1;
}

void	tokenizer(char *line, t_tokens **tokens)
{
	int	token_start;
	int	token_end;

	token_start = 0;
	token_end = 0;
	while (token_end <= ft_strlen(line))
	{
		// If the end of input is recognized, the current token (if any) shall
		// be delimited.
		if (line[token_end] == '\0' || line[token_end] == ' ' || line[token_end] == '	')
		{
			extract_node(tokens, &line[token_start], &token_start, &token_end - 1);
			token_end++;
			token_start = token_end;
		}
		// If the previous character was used as part of an operator and the
		// current character is not quoted and can be used with the previous
		// characters to form an operator, it shall be used as part of that (operator) token.
		else if (is_operator(line[token_end - 1]) && can_form_operator(line + token_end) && token_end - token_start == 2)
		{
			printf("#1\n");
			extract_node(tokens, &line[token_start], &token_start, &token_end);
			token_start = token_end;
//			printf("token_start is %c\ntoken_end is %c\n", line[token_start], line[token_end]);
//			extract_node(tokens, &line[token_start], &token_start, &token_end);
//			token_end++;
//			token_start = token_end + 1;
		}
		// If the previous character was used as part of an operator and the
		// current character cannot be used with the previous characters to form
		// an operator, the operator containing the previous character shall be delimited.
		else if (is_operator(line[token_start]) && !can_form_operator(line + token_end))
		{
			printf("#2\n");
//			printf("token_start is %c\ntoken_end is %c\n", line[token_start], line[token_end]);
			extract_node(tokens, &line[token_start], &token_start, &token_end - 1);
			token_start = token_end;
		}
		// If the current character is not quoted and can be used as the first
		// character of a new operator, the current token (if any) shall be
		// delimited. The current character shall be used as the beginning of
		// the next (operator) token.
		else if (is_operator(line[token_end]) && !is_operator(line[token_start]))
		{
			printf("#3\n");
//			printf("token_start is %c\ntoken_end is %c\n", line[token_start], line[token_end]);
			extract_node(tokens, &line[token_start], &token_start, &token_end - 1);
//			token_end++;
			token_start = token_end;
		}
		token_end++;
//		else if (is_operator(line[token_end]))
//		{
//			extract_node(tokens, &line[token_start], &token_start, &token_end);
//		}
//		else if (is_quote_character(line[token_start]))
//		{
//			// here I could token_end++ puisque je vais toujours commencer a regarder a partir du prochain char
//			if (line[token_start] == 92) // if character is backslash
//			{
//				token_end++;
//				add_token_node(tokens, &line[token_start], token_end - token_start + 1);
//			}
//			else
//			{
//				token_end++;
//				while (line[token_end] != line[token_start])
//					token_end++;
//				add_token_node(tokens, &line[token_start], token_end - token_start + 1);
//			}
//			token_start = token_end + 1;
//		}
//		else
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
		print_tokens(tokens);
	}
	return (0);
}

// tests
// ./tokenizer "a"
// ./tokenizer "a b c d e f gh ij kl mnop ejrkewjrkewjrkwejrwejkrew"
// operator tests
//
// quotes tests
//

