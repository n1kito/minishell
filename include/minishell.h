#ifndef MINISHELL_H
# define MINISHELL_H 

/*
typedef struct s_master
{
	t_tokens			*tokens;
	t_tokenizer_helpers	helpers;
	t_expand			expand_utils;	
	t_env				*env;
	int					malloc_success;
}	t_master;
*/

// INCLUDES
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "environment.h"
# include "tokenizer.h"
# include "parser.h"

// main.c

int	err_msg(char *error, int error_code);

#endif
