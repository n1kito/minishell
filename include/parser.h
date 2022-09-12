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
void		parser(t_tokens **tokens);
int			is_file_name_token(t_tokens *token);
int			is_operator_token(t_tokens *tokens);
void		print_parsed_tokens(t_tokens *tokens);

// parser_identify_tokens.c
void		identify_token_type(t_tokens *token);

// parser_syntax_checker.c
int			syntax_checker(t_tokens *tokens, t_master *master, int err);

// expander.c
void		expander(t_master *master);
void		remove_quotes(t_tokens **token_node, int first_quote,
			int second_quote, t_master *master);
void		process_and_remove_quotes(t_tokens *token_node, t_master *master);
int			expand_line(char **line, t_master *master);
void		check_for_invisible_tokens(t_tokens	*token);

// expander_analysers.c
char		*search_env(t_env *env, char *name, int name_len);
void		log_expansions(char *token, t_master *master);
void		expand_exit_code(t_master *master, t_expand *new_expand);
int			add_exp_node(t_master *master, char *token, int i);

// expander_analysers2.c
int			has_solitary_quote(char *token, t_master *master);
int			expansion_name_len(char *expansion);

// expander_utils.c
char		*str_join(char *token1, char *token2);
void		toggle_quoting(int *quoting_status);
int			count_expands(t_expand *expansions);
int			free_expansions(t_expand **expansions);
int			expand_token(t_tokens *token, t_master *master);

// expander_word_splitting.c
void		process_for_word_splitting(t_tokens **tokens_ptr, t_master *master_ptr);
void		insert_tokens(t_tokens **token_ptr, t_master *tmp_m, t_master *og_m);

// expander_word_splitting_analyser.c
int			token_has_unquoted_blanks(t_tokens *token);
int			has_single_quotes(char *str);

// expander_word_splitting_utils.c
t_tokens	*get_next_unsplitted_token(t_tokens *current);
int			get_next_non_blank_char(char *str);
void		set_tokens_as_words(t_tokens *token);

// to remove before pushing it's in the libft
int		ft_isdigit(int checkme);
#endif
