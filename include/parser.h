#ifndef PARSER_H
# define PARSER_H

// PARSING TOKEN TYPES
# define TOKEN 0 // default type assigned to all new tokenss
# define WORD 1 // pas encore pige la difference entre word et name mais bon
# define COMMAND_NAME 2
# define PIPE_TOKEN 3
# define REDIRECT_FROM 4
# define REDIRECT_TO 5
# define APPEND 6
# define FILE_NAME 7
# define HERE_DOC 8
# define DELIMITER 9
# define INVISIBLE 10

// parser.c
int		parser(t_tokens **tokens);
int		is_file_name_token(t_tokens *token);
int		is_operator_token(t_tokens *tokens);
void	print_parsed_tokens(t_tokens *tokens);

// parser_identify_tokens.c
void	identify_token_type(t_tokens *token);

// parser_syntax_checker.c
int		syntax_checker(t_master *master);

// expander.c
int		expander(t_master *master);
int		remove_quotes(t_tokens **token_node, int first_quote,
			int second_quote, t_master *master);
int		process_and_remove_quotes(t_tokens *token_node, t_master *master);
int		expand_line(char **line, t_expand *expansions);
void	check_for_invisible_token(t_tokens	*token);
int		process_for_word_splitting(t_tokens **token_ptr, t_master *master);

// expander_analysers.c
char	*search_env(t_env *env, char *name, int name_len);
int		log_expansions(char *token, t_master *master);
int		add_exp_node(t_master *master, char *token, int i);
int		has_solitary_quote(char *token, t_master *master);

// expander_word_splitting_utils.c
int		get_next_non_blank_char(char *str);
void	set_tokens_as_words(t_tokens *token);

// expander_utils.c
char	*str_join(char *token1, char *token2);
int		expansion_name_len(char *expansion);
void	toggle_quoting(int *quoting_status);
int		count_expands(t_expand *expansions);
int		free_expansions(t_expand **expansions);

// to remove before pushing it's in the libft
int		ft_isdigit(int checkme);
#endif
