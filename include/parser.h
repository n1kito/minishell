#ifndef PARSER_H
# define PARSER_H

// PARSING TOKEN TYPES
# define TOKEN 0
# define WORD 1
# define ASSIGNMENT_WORD 2
# define NAME 3
# define IO_NUMBER 4
# define REDIRECT_FROM 5
# define REDIRECT_TO 6
# define APPEND 7
# define HERE_DOC 8
# define PIPE_TOKEN 9

int		is_io_number_token(t_tokens *token);
void	parser(t_tokens **tokens);
int		is_operator_token(t_tokens *tokens);
int		is_only_digits(char *token);
void	print_parsed_tokens(t_tokens *tokens);
void	classify_as_simple_token(t_tokens *token);

#endif
