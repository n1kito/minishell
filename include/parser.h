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

void	parser(t_tokens *tokens);

#endif
