#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

// STRUCTURES
typedef struct s_env {
	char			*name;
	char			*variable;
	int				is_env;
	int				is_exported;
	struct s_env	*next;
}	t_env;

// parser_auotes_expansions.c
void	quote_expander(t_tokens **tokens, t_env *env);

#endif
