#ifndef TOKENIZER_H
# define TOKENIZER_H

// INCLUDES
#include <stdio.h>
#include <stdlib.h>

// STRUCTURES
typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

// DEFINES
// Blank Characters
#  define SPACE 32
#  define TAB 9
// Operator Characters
#  define PIPE 124
#  define LEFT_CHEVRON 60
#  define RIGHT_CHEVRON 62
// Quote Characters
#  define BACKSLASH 92
#  define SINGLE_QUOTE 39
#  define DOUBLE_QUOTE 34

// tokenizer.c
t_tokens	*get_last_token(t_tokens *tokens_list);
void		tokenizer(char *line, t_tokens **tokens);
// tokenizer_utils.c
int			ft_strlen(char *string);

#endif
