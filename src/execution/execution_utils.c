#include "minishell.h"

int	is_builtin_function(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	// TODO: Code strcmp ?? So we can compare both strings without supplying a lenght ? That would be super much better.
	if ((name_len == 6 && ft_strcmp(name, "export", name_len)) // do I need to ft_strlen ? Check the strcmp function, does it check that both strings are the same size ?
		|| (name_len == 5 && ft_strcmp(name, "unset", name_len))
		|| (name_len == 4 && ft_strcmp(name, "echo", name_len))
		|| (name_len == 3 && ft_strcmp(name, "pwd", name_len)) // not sure this one but probably
		|| (name_len == 2 && ft_strcmp(name, "cd", name_len)))
		return (1);
	return (0);
}
