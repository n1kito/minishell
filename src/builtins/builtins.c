#include "../../include/builtins.h"

/* Prints `name` variable of `list` nodes of type `variable_tupe`
 * by alphabetical order. */
void	print_list_by_alphabetical_order(t_env *list)
{
	t_env	*current;
	int		index;
	int		current_char;
	int		word_to_print;

	current = env;
	cursor_position = 0;
	while (current)
	{
		current->name[cursor_position];
	}
}

/* Outputs variables in the alphabetical order of their `name` variable.
 * First all environment variables, then user-defined exported variables.
 * All are preceded with "declare -x". */
void	print_exported_variables(t_env *env_list)
{
	print_list_by_alphabetical_order(env_list);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_env	env2;

	(void)argc;
	if (argc < 2 || argc % 2 == 0)
		printf("Need an even number of arguments and at least 2.\n");
	env.name = argv[1];
	env.variable = argv[2];
	env.next = &env2;
	env.variable_type = 1;
	env2.name = argv[3];
	env2.variable = argv[4];
	env2.variable_type = 1;
	env2.next = 0;
//	printf("%s=%s\n", env.name, env.variable);
//	printf("%s=%s\n", env2.name, env2.variable);
	print_exported_variables(&env);
	return (0);
}
