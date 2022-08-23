#include "minishell.h"

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
int	log_expansions(char *token, t_env *env, t_master *master)
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
			&& token[i + 1]
			&& !is_blank_char(token[i + 1])
			&& !is_single_quoting
			&& !(is_quote_character(token [i + 1]) && is_double_quoting))
		{
			if (!add_exp_node(master, token, i, env))
				return (0);
		}
		else if (token[i] == DOUBLE_QUOTE && !is_single_quoting)
			toggle_quoting(&is_double_quoting);
		else if (token[i] == SINGLE_QUOTE && !is_double_quoting)
			toggle_quoting(&is_single_quoting);
		i++;
	}
	return (1);
}

/* Logs new node in expansion structure to track expansions, their positions and
 * values (if found in env). Note that they are added LIFO. */
int	add_exp_node(t_master *master, char *token, int i, t_env *env)
{
	t_expand	*new_expand;

	new_expand = malloc(sizeof(t_expand));
	if (!new_expand)
		return (err_msg("malloc failed [add_exp_node()]", 0, master));
	new_expand->start = i;
	new_expand->name_start = i + 1;
	new_expand->name_len = expansion_name_len(token + i);
	new_expand->name_end = i + new_expand->name_len;
	new_expand->name = token + new_expand->name_start;
	new_expand->value = search_env(env, new_expand->name,
			new_expand->name_len);
	new_expand->next = NULL;
	if (master->expansions == NULL)
		master->expansions = new_expand;
	else
	{
		new_expand->next = master->expansions;
		master->expansions = new_expand;
	}
	return (1);
}

/* Checks that there is no quote without a matching quote. */
int	has_solitary_quote(char *token, t_master *master)
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
				return (err_msg("open quote", 1, master));
		}
		else
			i++;
	}
	return (0);
}
