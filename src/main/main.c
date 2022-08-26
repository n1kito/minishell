
#include "minishell.h"
#include "builtin.h"
#include "environment.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	get_env(envp, &env);
	ft_export(&env, (argv + 1));
	ft_env(env);
	return (0);
}
