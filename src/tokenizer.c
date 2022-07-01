#include <stdio.h>
#include <stdlib.h>

/*

The tokenizer() function follows the shell guidelines.

The shell shall read its input in terms of lines. (For details about how the shell reads its input, see the description of sh.) The input lines can be of unlimited length. These lines shall be parsed using two major modes: ordinary token recognition and processing of here-documents.
When an io_here token has been recognized by the grammar (see Shell Grammar), one or more of the subsequent lines immediately following the next NEWLINE token form the body of one or more here-documents and shall be parsed according to the rules of Here-Document.
When it is not processing an io_here, the shell shall break its input into tokens by applying the first applicable rule below to the next character in its input. The token shall be from the current position in the input until a token is delimited according to one of the rules below; the characters forming the token are exactly those in the input, including any quoting characters. If it is indicated that a token is delimited, and no characters have been included in a token, processing shall continue until an actual token is delimited.

1. If the end of input is recognized, the current token (if any) shall be delimited.
2. If the previous character was used as part of an operator and the current character is not quoted and can be used with the previous characters to form an operator, it shall be used as part of that (operator) token.
3. If the previous character was used as part of an operator and the current character cannot be used with the previous characters to form an operator, the operator containing the previous character shall be delimited.
4. If the current character is <backslash>, single-quote, or double-quote and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. The rules for quoting are as described in Quoting . During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, including any embedded or enclosing quotes or substitution operators, between the <quotation-mark> and the end of the quoted text. The token shall not be delimited by the end of the quoted field.
5. If the current character is an unquoted '$' or '`', the shell shall identify the start of any candidates for parameter expansion (Parameter Expansion), command substitution (Command Substitution), or arithmetic expansion (Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.
6. If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.
7. If the current character is an unquoted <blank>, any token containing the previous character is delimited and the current character shall be discarded.
8. If the previous character was part of a word, the current character shall be appended to that word.
9. If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.
10. The current character is used as the start of a new word.

Once a token is delimited, it is categorized as required by the grammar in Shell Grammar.

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

void	tokenizer(char *line, t_tokens **tokens)
{
	int token_start;
	int token_end;

	token_start = 0;
	token_end = 0;

	while (token_end <= ft_strlen(line))
	{
		if (line[token_end] == '\0' || line[token_end] == ' ' || line[token_end] == '	')
		{
			add_token_node(tokens, &line[token_start], token_end - token_start);
			token_start = token_end + 1;
		}
		token_end++;
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
