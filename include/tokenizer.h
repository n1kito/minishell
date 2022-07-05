#ifndef TOKENIZER_H
# define TOKENIZER_H

// INCLUDES
#include <stdio.h>
#include <stdlib.h>

# ifdef VISUAL
#  define ONE printf("[Rule 1] ");
#  define TWO printf("[Rule 2] ");
#  define THREE printf("[Rule 3] ");
#  define FOUR printf("[Rule 4] ");
#  define FIVE printf("[Rule 5] ");
#  define SIX printf("[Rule 6] ");
#  define SEVEN printf("[Rule 7] ");
#  define EIGHT printf("[Rule 8] ");
#  define NINE printf("[Rule 9] ");
#  define TEN printf("[Rule 10] ");
#  define PLUS printf("+ ");
#  define NEWLINE printf("\n");
#  define ARGUMENT printf(" %s\n", argv[1]);
#  define COLOR_CROCHET_START printf("\033[0;35m[\033[0m");
#  define COLOR_CROCHET_END printf("\033[0;35m]\033[0m\n");
#  define PIPE printf("\033[0;35m|\033[0m");
# else
#  define ONE
#  define TWO
#  define THREE
#  define FOUR
#  define FIVE
#  define SIX
#  define SEVEN
#  define EIGHT
#  define NINE
#  define TEN
#  define PLUS
#  define NEWLINE
#  define ARGUMENT
#  define COLOR_CROCHET_START printf("[");
#  define COLOR_CROCHET_END printf("]\n");
#  define PIPE printf("|");
# endif

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
//#  define PIPE 124
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
