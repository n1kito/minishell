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

typedef struct s_env {
	char			*name;
	char			*variable;
	int				is_env;
	struct s_env	*next;
}	t_env;

// INCLUDES
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "environment.h"
# include "tokenizer.h"
# include "parser.h"
# include "execution.h"
# include "signals.h"

// main.c

// minishell_utils.c
int		err_msg(char *error, int error_code, t_master *master);
void	init_master_structure(t_master *master, char *envp[]);
int		free_master(t_master *master, int return_value);

#endif
