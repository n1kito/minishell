#include "../../include/minishell.h"

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
	t_master			master;
	t_env				*env;
	t_env				variable1;
	t_env				variable2;
	t_env				variable3;
	char				name1[5]="USER";
	char				name2[6]="SHELL";
	char				name3[6]="QUOTE";
	char				value1[7]="nikito";
	char				value2[5]="bash";
	char				value3[2]="'";

	env = &variable1;
	variable1.name = name1;
	variable1.variable = value1;
	variable1.next = &variable2;
	variable2.name = name2;
	variable2.variable = value2;
	variable2.next = &variable3;
	variable3.name = name3;
	variable3.variable = value3;
	variable3.next = NULL;
	init_master_structure(&master, env);
	init_tokenizer_helpers(&master.helpers, argv[1]);
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &master, &master.helpers);
		parser(&master.tokens);
		NEWLINE
		if (expander(&master))
			print_tokens(master.tokens);
		else
			printf("Error: Open quote.\n");
	} 
	return (0);
}
