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
										else if (current->token_type == 11)
												printf("INVISIBLE");
				                        else
				                                printf("UNKNOWN");
				                        if (current->next)
				                                PIPE_PRINT
				                        current = current->next;
				                }
                COLOR_CROCHET_END
}

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
	t_env				*env;
	t_env				variable1;
	t_env				variable2;
	char				name1[5]="USER";
	char				name2[6]="SHELL";
	char				value1[7]="nikito";
	char				value2[5]="bash";

	env = &variable1;
	variable1.name = name1;
	variable1.variable = value1;
	variable1.next = &variable2;
	variable2.name = name2;
	variable2.variable = value2;
	variable2.next = NULL;
	init_tokenizer_helpers(&t, argv[1]);
	tokens = NULL;
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &tokens, &t);
		parser(&tokens);
		NEWLINE
		if (expander(&tokens, env))
			print_tokens(tokens);
		else
			printf("Error: Open quote.\n");
	} 
	print_parsed_tokens(tokens);
	return (0);
}
