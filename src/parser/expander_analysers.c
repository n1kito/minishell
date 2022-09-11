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
void	log_expansions(char *token, t_master *master)
{
	int	i;
	int	is_single_quoting;
	int	is_double_quoting;

	is_single_quoting = 0;
	is_double_quoting = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '$' && token[i + 1] && !is_single_quoting
			&& !is_blank_char(token[i + 1])
			&& !(is_quote_character(token [i + 1]) && is_double_quoting)
			&& (ft_isalpha(token[i + 1])
				|| token[i + 1] == '_' || token[i + 1] == '?'))
		{
			if (!add_exp_node(master, token, i))
				exit(free_all(master, 1) 
					&& err_msg("failed to log expansions [log_expansions()]",
						1, master));
		}
		else if (token[i] == DOUBLE_QUOTE && !is_single_quoting)
			toggle_quoting(&is_double_quoting);
		else if (token[i] == SINGLE_QUOTE && !is_double_quoting)
			toggle_quoting(&is_single_quoting);
	}
}

/* Expands the value of the global g_minishesit code variable and stores it
 * in the master structure so it can be freed later. */
void	expand_exit_code(t_master *master, t_expand *new_expand)
{
	free(master->exit_code);
	master->exit_code = ft_itoa(g_minishexit);
	if (!master->exit_code)
	{
		free(new_expand);
		exit(err_msg("itoa() failed [expand_exit_code()]", 1, master)
			&& free_all(master, 1));
	}
	new_expand->value = master->exit_code;
}

/* Logs new node in expansion structure to track expansions, their positions and
 * values (if found in env). Note that they are added LIFO. */
int	add_exp_node(t_master *master, char *token, int i)
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
	if (token[i + 1] == '?')
		expand_exit_code(master, new_expand);
	else
		new_expand->value = search_env(master->env, new_expand->name,
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
