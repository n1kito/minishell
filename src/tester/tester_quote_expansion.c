#include "../../include/minishell.h"

void	setup_env_variables(t_env **env)
{
	t_env	variable1;
	t_env	variable2;
	char	name1[5]="USER";
	char	name2[6]="SHELL";
	char	value1[7]="nikito";
	char	value2[5]="bash";

	*env = &variable1;
	variable1.name = name1;
	variable1.variable = value1;
	variable1.next = &variable2;
	variable2.name = name2;
	variable2.variable = value2;
	variable2.next = NULL;
}

/* Only used to test the tokenizer.
 * /!\ The init_tokenizer_helpers() function will need to be used in the main
 * code, before using the tokenizer. */
int	main(int argc, char **argv)
{
	t_tokens			*tokens;
	t_tokenizer_helpers	t;
	t_env				*env;

	setup_env_variables(&env);
	init_tokenizer_helpers(&t, argv[1]);
	tokens = NULL;
	if (argc != 2)
		printf("Error\n> %s needs a quoted string in argv[1].\n", argv[0]);
	else
	{
		ARGUMENT
		tokenizer(argv[1], &tokens, &t);
		NEWLINE
		quote_expander(&tokens, env);
		print_tokens(tokens);
	} 
	return (0);
}
