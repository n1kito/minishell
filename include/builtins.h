#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_env {
	char			*name;
	char			*variable;
	int				is_env;
	int				is_exported;
	struct s_env	*next;
}	t_env;

//builtins_export_print.c
void	sort_table_alphabetically(t_env **sorting_table, int list_len);
void	populate_sorting_table(t_env *list, t_env **sorting_table, int list_len);
void	print_env_by_alphabetical_order(t_env *list);

// builtins_utils.c
int	ft_strcmp(const char *first, const char *second);
int	is_sorted_list(t_env *list[]);
int	lstlen(t_env *list);