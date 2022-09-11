#include "minishell.h"

int	process_for_word_splitting(t_tokens **token_ptr, t_master *master_ptr)
{
	t_master	tmp_master;
	char		*token;
	int			position;
	int			token_start;
	int			expansion_status;

	printf("word splitting\n");
	token = (*token_ptr)->token;
	position = 0;
	token_start = 0;
	expansion_status = (*token_ptr)->was_expanded;
	init_master_structure(&tmp_master);
	while (position <= (int)ft_strlen(token))
	{
		if (token[position] == '\0')
		{
			if (!extract_token(&tmp_master, &token[token_start], &token[position - 1]))
				return (0);
			position++;
			get_last_token(tmp_master.tokens)->word_splitted = 1;
			get_last_token(tmp_master.tokens)->was_expanded = expansion_status;
		}
		else if (token[position] == DOUBLE_QUOTE)
			position += find_matching_quote(&token[position]) + 1; // check this
		else if (is_blank_char(token[position]))
		{
			if (!extract_token(&tmp_master, &token[token_start], &token[position - 1]))
				return (0);
			position += get_next_non_blank_char(&token[position]);
			token_start = position;
			get_last_token(tmp_master.tokens)->word_splitted = 1;
			get_last_token(tmp_master.tokens)->was_expanded = expansion_status;
		}
		else
			position++;
	}
	//TODO move this to insert_splitted_tokens()
	set_tokens_as_words(tmp_master.tokens);
	tmp_master.tokens->previous = (*token_ptr)->previous;
	get_last_token(tmp_master.tokens)->next = (*token_ptr)->next;
	if ((*token_ptr)->previous)
	{
		(*token_ptr)->previous->next = tmp_master.tokens;
		free((*token_ptr)->token);
		free(*token_ptr);
		(*token_ptr) = tmp_master.tokens;
	}
	else
	{
		free((*token_ptr)->token);
		free(*token_ptr);
		master_ptr->tokens = tmp_master.tokens;
		(*token_ptr) = master_ptr->tokens;
	}
	return (1);
}
