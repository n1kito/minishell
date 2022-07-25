#include "../../include/tokenizer.h"
#include "../../include/minishell.h"

/* Prints the tokens in a visual manner ✨. */
void	print_tokens(t_tokens *tokens)
{
	t_tokens	*current;

	COLOR_CROCHET_START
	current = tokens;
	while (current)
	{
		printf("%s", current->token);
		if (current->next)
			PIPE_PRINT
		current = current->next;
	}
	COLOR_CROCHET_END
}

/* Only used to test the tokenizer.
 * /!\ The init_tokenizer_helpers() function will need to be used in the main
 * code, before using the tokenizer. */
int	main(int argc, char **argv)
{
	t_tokens			*tokens;
	t_tokenizer_helpers	t;

	init_tokenizer_helpers(&t, argv[1]);
	tokens = NULL;
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &tokens, &t);
		NEWLINE
		print_tokens(tokens);
	} 
	parser(&tokens);
	print_parsed_tokens(tokens);
	return (0);
}
