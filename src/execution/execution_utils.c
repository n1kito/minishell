#include "minishell.h"

int	is_builtin_function(char *name)
{
	int	name_len;

	name_len = ft_strlen(name);
	if (!name_len)
		return (0);
	if (ft_strcmp(name, "export", name_len) == 0
		|| ft_strcmp(name, "unset", name_len) == 0
		|| ft_strcmp(name, "echo", name_len) == 0
		|| ft_strcmp(name, "pwd", name_len) == 0 // not sure this one but probably
		|| ft_strcmp(name, "cd", name_len) == 0)
		return (1);
	return (0);
}
