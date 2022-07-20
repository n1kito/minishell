#ifndef PARSER_H
# define PARSER_H

// INCLUDES
# include <stdio.h>
# include <stdlib.h>
# include "tokenizer.h"

// PARSING TOKEN TYPES
# define WORD 1
# define ASSIGNMENT_WORD 2
# define NAME 3
# define IO_NUMBER 4
# define REDIRECT_FROM 5
# define REDIRECT_TO 5
# define APPEND 6
# define HERE_DOC 7
# define PIPE 8

void	parser(t_tokens **tokens);
int		is_operator_token(t_tokens *tokens);

#endif
