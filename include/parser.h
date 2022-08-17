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
# define IO_NUMBER 8
# define HERE_DOC 9
# define DELIMITER 10
# define INVISIBLE 11

// parser.c
int		is_io_number_token(t_tokens *token);
void	parser(t_tokens **tokens);
int		is_operator_token(t_tokens *tokens);
int		is_only_digits(char *token);
void	print_parsed_tokens(t_tokens *tokens);

// parser_identify_tokens.c
void	identify_token_type(t_tokens *token);

// parser_syntax_checker.c
int		syntax_checker(t_tokens *tokens);

// expander.c
void	remove_quotes(t_tokens **token_node, int first_quote, int second_quote);
void	add_exp_node(t_expand **expansions, char *token, int i, t_env *env);
void	expand_token(t_tokens *current, t_expand *expansions);
void	process_and_remove_quotes(t_tokens *token_node);
int		expander(t_tokens **tokens, t_env *env);

// expander_analysers.c
char	*search_env(t_env *env, char *name, int name_len);
void	log_expansions(char *token, t_env *env, t_expand **expansions);
int		has_single_quote(char *token);

// expander_utils.c
char	*str_join(char *token1, char *token2);
int		expansion_name_len(char *expansion);
void	toggle_quoting(int *quoting_status);
int		count_expands(t_expand *expansions);
void	free_expansions(t_expand **expansions);

// to remove before pushing it's in the libft
int		ft_isdigit(int checkme);
#endif
