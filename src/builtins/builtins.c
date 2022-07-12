#include "../../include/builtins.h"

int	main(int argc, char *argv[])
{
	t_env	env;
	t_env	env2;

	(void)argc;
	env.name = argv[1];
	env.variable = argv[2];
	env.next = &env2;
	env2.name = argv[3];
	env2.variable = argv[4];
//	printf("%s=%s\n", env.name, env.variable);
//	printf("%s=%s\n", env2.name, env2.variable);
	return (0);
}