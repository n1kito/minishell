#include "minishell.h"

extern void	print_tokens(t_master *master)
{
	t_tokens *current;

	current = master->tokens;
	while (current)
	{
		printf("%s", current->token);
		if (current->next)
			printf("\e[2m░\e[0m");
		else
			printf("\n");
		current = current->next;
	}
}

int	token_has_unquoted_blanks(t_tokens *token)
{
	int	i;

	printf("looking for unquoted blanks\n");
	i = 0;
	while (token->token[i])
	{
		if (token->token[i] == DOUBLE_QUOTE)
			i += find_matching_quote(&token->token[i]) + 1;
		else if (is_blank_char(token->token[i]))
		{
			printf("found an unquoted blank\n");
			return (1);
		}
		else
			i++;
	}
	printf("did not find any unquoted blanks\n");
	return (0);
}

t_tokens	*get_next_unsplitted_token(t_tokens *current)
{
	current = current->next;
	while (current)
	{
		if (current->word_splitted == 0)
			return (current);
		else
			current = current->next;
	}
	return (current);
}

int	has_single_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
			i += find_matching_quote(&str[i]) + 1;
		if (str[i] == SINGLE_QUOTE && find_matching_quote(&str[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

/* Goes through tokens, checks that there are no single quotes.
 * If there are not, identifies variables to expand and expands them.
 * Then removes all removable quotes. */
int	expander(t_master *master)
{
	t_tokens	*current;

	//TODO move this to another function, maybe the one in main.c, found_open_quotes()
	current = master->tokens;
	while (current)
	{
		if (has_solitary_quote(current->token, master) && !current->word_splitted)
			return (0);
		current = current->next;
	}
	print_tokens(master);
	current = master->tokens;
	while (current)
	{
			if (current->token_type != DELIMITER)
			{
				printf("processing expansions\n");
				if (!log_expansions(current->token, master))
					return (err_msg("failed to log expansions [expander()]",
							0, master));
				if (master->expansions)
				{
					if (!expand_line(&current->token, master->expansions))
						return (err_msg("failed to expand [expander()]",
								0, master));
					current->was_expanded = 1;
				}
				free_expansions(&master->expansions);
			}
			print_tokens(master);
			//process word splitting on token
			printf("[TREATING] %s\n", current->token);
			if (token_has_unquoted_blanks(current)
					&& !process_for_word_splitting(&current, master))
				return (0);
			else
				if (!process_and_remove_quotes(current, master))
					return (0);
			printf("%s (word splitted: %d + expanded: %d)\n", current->token, current->word_splitted, current->was_expanded);
			current = get_next_unsplitted_token(current);
		//current = current->next;
	}
	printf("tokens now are: ");
	print_tokens(master);
	//change the following functions to work with tokens
	current = master->tokens;
	while (current)
	{
		/*
	//	if ((current->word_splitted && !current->was_expanded))
	//	{
	//		printf("removing quotes 1 from %s\n", current->token);
	//		if (!process_and_remove_quotes(current, master))
	//			return (0);
	//	}
		if (current->was_expanded
			&& !current->word_splitted
			&& !has_single_quotes(current->token))
		{
			printf("removing quotes 2 from %s\n", current->token);
			if (!process_and_remove_quotes(current, master))
				return (0);
		}
		else if (!current->word_splitted && !current->was_expanded)
		{
			printf("removing quotes 2 from %s\n", current->token);
			if (!process_and_remove_quotes(current, master))
				return (0);
		}*/
		check_for_invisible_token(current);
		current = current->next;
	}
	printf("tokens now are: ");
	print_tokens(master);
	return (1);
}

int	get_next_non_blank_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_blank_char(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	set_tokens_as_words(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		current->token_type = WORD;
		current->was_expanded = 1;
		current = current->next;
	}
}

/* Goes through token and removes pairs of quotes. */
int	process_and_remove_quotes(t_tokens *token_node, t_master *master)
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
			if (token_node->token_had_quotes == 0)
				token_node->token_had_quotes = 1;
			matching_quote_pos = find_matching_quote(token_node->token + i);
			if (!remove_quotes(&token_node, i, matching_quote_pos, master))
				return (0);
			i += matching_quote_pos - 1;
		}
		else
			i++;
	}
	return (1);
}

/* Removes quote pairs from current token. */
int	remove_quotes(t_tokens **token_node, int quote1, int quote2, t_master *m)
{
	char	*concatenate_me;
	char	*tmp_token;

	concatenate_me = (*token_node)->token + quote1 + quote2 + 1;
	(*token_node)->token[quote1 + quote2] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][1]", 0, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
	concatenate_me = (*token_node)->token + quote1 + 1;
	(*token_node)->token[quote1] = '\0';
	tmp_token = str_join((*token_node)->token, concatenate_me);
	if (!tmp_token)
		return (err_msg("malloc() failed [remove_quotes()][2]", 0, m));
	free((*token_node)->token);
	(*token_node)->token = tmp_token;
	return (1);
}

/* Expands all expansions, back to front. */
// Actually this should be move to a file that has to do with heredocs
// I am coding a separate expand_token function
int	expand_line(char **line, t_expand *expansions)
{
	char		*tmp_token;
	char		*new_token;
	t_expand	*exp;

	exp = expansions;
	while (exp)
	{
		tmp_token = str_join(exp->value, *line + exp->name_end + 1);
		if (!tmp_token)
			return (0);
		*(*line + exp->start) = '\0';
		new_token = str_join(*line, tmp_token);
		if (!new_token)
		{
			free(tmp_token);
			return (0);
		}
		free(tmp_token);
		tmp_token = *line;
		*line = new_token;
		free(tmp_token);
		exp = exp->next;
	}
	return (1);
}

/* If the token passed as parameter is of type WORD, is empty
 * and did not initially have empty quotes in it, it will be 
 * typed as INVISIBLE. */
void	check_for_invisible_token(t_tokens *token)
{
	if (token->token_type == WORD
		&& token->token[0] == '\0'
		&& !token->token_had_quotes)
		token->token_type = INVISIBLE;
}
