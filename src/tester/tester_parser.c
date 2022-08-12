#include "../../include/tokenizer.h"
#include "../../include/minishell.h"

/* Prints the type of each token */
void	print_parsed_tokens(t_tokens *tokens)
{
                t_tokens        *current;

                current = tokens;
                COLOR_CROCHET_START
                while (current)
                {
				                        if (current->token_type == 0)
				                                printf("TOKEN");
				                        else if (current->token_type == 1)
				                                printf("WORD");
				                        else if (current->token_type == 2)
				                                printf("COMMAND");
				                        else if (current->token_type == 3)
				                                printf("PIPE");
				                        else if (current->token_type == 4)
				                                printf("REDIRECT_FROM");
				                        else if (current->token_type == 5)
				                                printf("REDIRECT_TO");
				                        else if (current->token_type == 6)
				                                printf("APPEND");
				                        else if (current->token_type == 7)
				                                printf("FILE_NAME");
				                        else if (current->token_type == 8)
				                                printf("IO_NUMBER");
				                        else if (current->token_type == 9)
				                                printf("HERE_DOC");
				                        else if (current->token_type == 10)
				                                printf("DELIMITER");
				                        else
				                                printf("UNKNOWN");
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
		parser(&tokens);
		if (syntax_checker(tokens))
			print_parsed_tokens(tokens);
		else
			printf("Syntax error.\n");
	} 
	return (0);
}
