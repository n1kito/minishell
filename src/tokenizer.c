#include <stdio.h>
#include <stdlib.h>

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
		return ;
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

int	is_an_operator(char c)
{
	if (c && (c == '<' || c == '>' || c == '|'))
		return (1);
	return (0);
}

int	is_quote_character(char c)
{
	if (c == 92 || c == 39 || c == 34)
		return (1);
	return (0);
}

void	tokenizer(char *line, t_tokens **tokens)
{
	int	token_start;
	int	token_end;

	token_start = 0;
	token_end = 0;
	while (token_end <= ft_strlen(line))
	{
		// handle blank spaces
		if (line[token_end] == '\0' || line[token_end] == ' ' || line[token_end] == '	')
		{
			add_token_node(tokens, &line[token_start], token_end - token_start);
			token_start = token_end + 1;
		}
		// handle operators
		else if (is_an_operator(line[token_start]))
		{
			if (is_an_operator(line[token_start + 1]))
			{
				token_end++;
				add_token_node(tokens, &line[token_start], token_end - token_start + 1);
			}
			else
			{
				add_token_node(tokens, &line[token_start], token_end - token_start + 1);
			}
			token_start = token_end + 1;
		}
		// TODO : add quoting handling
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
