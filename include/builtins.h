#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_env {
	char *name;
	char *variable;
	struct s_env *next;
}	t_env;