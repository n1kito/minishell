#include "../include/tokenizer.h"

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

int ft_strlen(char *string)
{
	int i;

	i = 0;
	while (string[i])
		i++;
	return (i);
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
// ./tokenizer " ||>ab bc|||>>>>|>   a " (copy paste is if it looks weird in CLION, it's because | + > is recognized as one symbol)
// [||||>|ab|bc|||||||>>|>>|||>|a]
//
// quotes tests
//
