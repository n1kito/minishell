#include "../../include/minishell.h"

/* Search for variable name in env.
 * Returns variable value if found, NULL if not. */
char	*search_env(t_env *env, char *name, int name_len)
{
	t_env	*current;
	int		i;

	current = env;
	while (current)
	{
		i = 0;
		while (current->name[i] == name[i] && i < name_len)
			i++;
		if (i == name_len && current->name[i] == '\0')
			return (current->variable);
		else
			current = current->next;
	}
	return (NULL);
}

/* Goes through token and logs expandable variables in a special structure. */
void	log_expansions(char *token, t_env *env, t_expand **expansions)
{
	int			i;
	int			is_single_quoting;
	int			is_double_quoting;

	is_single_quoting = 0;
	is_double_quoting = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$'
			&& expansion_name_len(token + i)
			&& !is_single_quoting)
		{
			add_exp_node(expansions, token, i, env);
		}
		else if (token[i] == DOUBLE_QUOTE && !is_single_quoting)
		{
			toggle_quoting(&is_double_quoting);
		}
		else if (token[i] == SINGLE_QUOTE && !is_double_quoting)
		{
			toggle_quoting(&is_single_quoting);
		}
		i++;
	}
}

/* Checks that there is no quote without a matching quote. */
int	has_single_quote(char *token)
{
	int	i;
	int	matching_quote;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == SINGLE_QUOTE || token[i] == DOUBLE_QUOTE)
		{
			matching_quote = find_matching_quote(&token[i]);
			if (matching_quote)
				i += matching_quote + 1;
			else
				return (0);
		}
		else
			i++;
	}
	return (1);
}
