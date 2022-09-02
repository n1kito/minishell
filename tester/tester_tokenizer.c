#include "minishell.h"

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
	t_master	master;

	init_master_structure(&master, NULL);
	init_tokenizer_helpers(&master.helpers, argv[1]);
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &master, &master.helpers);
		NEWLINE
		print_tokens(master.tokens);
	} 
	return (0);
}
