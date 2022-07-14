#include "../../include/builtins.h"

int	main(int argc, char *argv[])
{
	t_env	env;
	t_env	env2;
	t_env	env3;

	(void)argc;
	if (argc < 2)
		printf("Need at least 2 arguments after program name.\n");
	env.name = argv[1];
	env.variable = argv[2];
	env.next = &env2;
	env.is_env = 1;
	env2.name = argv[3];
	env2.variable = argv[4];
	env2.is_env = 1;
	env2.next = &env3;
	env3.name = argv[5];
	env3.variable = argv[6];
	env3.is_env = 1;
	env3.next = NULL;
	print_env_by_alphabetical_order(&env);
	return (0);
}
