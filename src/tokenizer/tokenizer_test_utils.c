#include "../../include/tokenizer.h"

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

int	main(int argc, char **argv)
{
	t_tokens	*tokens;

	tokens = NULL;
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &tokens);
		NEWLINE
		print_tokens(tokens);
	}
	return (0);
}
