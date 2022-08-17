#include "../../include/minishell.h"

char	*str_join(char *token1, char *token2)
{
	char	*new_token;
	int		i;
	int		j;

	new_token = malloc(sizeof(char)
			* ((ft_strlen(token1) + ft_strlen(token2)) + 1));
	if (!new_token)
		return (NULL);
	i = 0;
	while (token1 && token1[i])
	{
		new_token[i] = token1[i];
		i++;
	}
	j = 0;
	while (token2 && token2[j])
		new_token[i++] = token2[j++];
	new_token[i] = '\0';
	return (new_token);
}

/* Removes single quotes from current token */
void	quote_remover(t_tokens **token_node, int first_quote, int second_quote)
{
	char	*concatenate_me;
	char	*tmp_token;
	char	*token;

	token = (*token_node)->token;
	concatenate_me = token + first_quote + second_quote + 1;
	token[first_quote + second_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	token = tmp_token;
	concatenate_me = token + first_quote + 1;
	token[first_quote] = '\0';
	tmp_token = str_join(token, concatenate_me);
	token = tmp_token;
	(*token_node)->token = token;
}

int	expansion_name_len(char *expansion)
{
	int	i;

	expansion++;
	i = 0;
	while (expansion[i]
		&& !is_blank_char(expansion[i])
		&& !is_quote_character(expansion[i])
		&& expansion[i] != '$')
			i++;
	return (i);
}

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

/* Logs new node in expansion structure to track expansions, their positions and
 * values (if found in env). Note that they are added LIFO. */
void	add_exp_node(t_expand **expansions, char *token, int i, t_env *env)
{
	t_expand	*new_expand;

	new_expand = malloc(sizeof(t_expand));
	if (!new_expand)
		return ;
	new_expand->start = i;
	new_expand->name_start = i + 1;
	new_expand->name_len = expansion_name_len(token + i);
	new_expand->name_end = i + new_expand->name_len;
	new_expand->name = token + new_expand->name_start;
	new_expand->value = search_env(env, new_expand->name,
			new_expand->name_len);
	new_expand->next = NULL;
	if (*expansions == NULL)
		*expansions = new_expand;
	else
	{
		new_expand->next = *expansions;
		*expansions = new_expand;
	}
}

void	toggle_quoting(int *boolean)
{
	if (*boolean == 0)
		*boolean = 1;
	else
		*boolean = 0;
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

int	count_expands(t_expand *expansions)
{
	int			count;
	t_expand	*current;

	current = expansions;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	expand_token(t_tokens *current, t_expand *expansions)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, &current->token[exp->name_end + 1]);
		current->token[exp->start] = '\0';
		new_token = str_join(current->token, tmp_token);
		free(tmp_token);
		tmp_token = current->token;
		current->token = new_token;
		free(tmp_token);
		exp = exp->next;
	}
}

void	free_expansions(t_expand **expansions)
{
	t_expand		*current;
	t_expand		*next;

	current = *expansions;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*expansions = NULL;
}

void	remove_quotes(t_tokens *token_node)
{
	int		i;
	int		matching_quote_pos;

	i = 0;
	while (token_node->token && token_node->token[i])
	{
		if ((token_node->token[i] == SINGLE_QUOTE
				|| token_node->token[i] == DOUBLE_QUOTE)
			&& find_matching_quote(token_node->token + i))
		{
			matching_quote_pos = find_matching_quote(token_node->token + i);
			quote_remover(&token_node, i, matching_quote_pos);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
}

int	check_quote_numbers(char *token)
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

// TODO add comments to all functions
// TODO divide files
// TODO work on error handling in this particular function
int	expand_tokens(t_tokens **tokens, t_env *env)
{
	t_tokens	*current;
	t_expand	*expansions;

	expansions = NULL;
	current = *tokens;
	while (current)
	{
		if (!check_quote_numbers(current->token))
		{
			printf("Error: Open quote.\n");
			return (0);
		}
		log_expansions(current->token, env, &expansions);
		if (expansions)
		{
			expand_token(current, expansions);
			free_expansions(&expansions);
		}
		remove_quotes(current);
		current = current->next;
	}
	return (1);
}
