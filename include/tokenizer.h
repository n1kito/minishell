#ifndef TOKENIZER_H
# define TOKENIZER_H

// INCLUDES
#include <stdio.h>
#include <stdlib.h>

# ifdef VISUAL
#  define ONE printf("[1]");
#  define TWO printf("[2]");
#  define THREE printf("[3]");
#  define FOUR printf("[4]");
#  define FIVE printf("[5]");
#  define SIX printf("[6]");
#  define SEVEN printf("[7]");
#  define EIGHT printf("[8]");
#  define NINE printf("[9]");
#  define TEN printf("[10]");
#  define PLUS printf("\033[0;33m+\033[0m");
#  define NEWLINE printf("\n");
#  define ARGUMENT printf(" %s\n", argv[1]);
#  define COLOR_CROCHET_START printf("\033[0;35m[\033[0m");
#  define COLOR_CROCHET_END printf("\033[0;35m]\033[0m\n");
#  define PIPE_PRINT printf("\033[0;35m|\033[0m");
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
#  define PIPE_PRINT printf("|");
# endif

// STRUCTURES
typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_tokenizer
{
	int				token_start;
	int				position;
	int				quote_match_found;
	char			*line;
}	t_tokenizer_helpers;

// DEFINES
// Blank Characters
# define SPACE 32
# define TAB 9
// Operator Characters
# define PIPE 124
# define L_CHEVRON 60
# define R_CHEVRON 62
// Quote Characters
//# define BACKSLASH 92
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

// tokenizer.c
void		tokenizer(char *line, t_tokens **tokens, t_tokenizer_helpers *t);

// tokenizer_utils.c
void		init_tokenizer_helpers(t_tokenizer_helpers *t, char *line);
t_tokens	*get_last_token(t_tokens *tokens_list);
void		extract_token(t_tokens **tokens, char *token_start, char *token_end);
int			ft_strlen(char *string); //TODO Remove this

// tokenizer_analysers.c
int			is_operator(char c);
int			is_quote_character(char c);
int			is_blank_char(char c);

// tokenizer_analysers_2.c
int			find_matching_quote(char *str);
int			can_form_operator(char *token_start, char *second_operator);
int			follows_token(char *line, int position, int quote_match_found);
int			follows_word(char *line, int position, int quote_match_found);

// tokenizer_handlers.c
void		handle_end_of_line(t_tokenizer_helpers *t, t_tokens **tokens);
void		handle_quotes(t_tokenizer_helpers *t, t_tokens **tokens);
void		handle_blank_char(t_tokenizer_helpers *t, t_tokens **tokens);

// tokenizer_handler_2.c
void		start_expansion_token(t_tokenizer_helpers *t, t_tokens **tokens);
void		start_operator_token(t_tokenizer_helpers *t, t_tokens **tokens);
void		close_operator_token(t_tokenizer_helpers *t, t_tokens **tokens);

// tokenizer_test_utils.c
void		print_tokens(t_tokens *tokens);

#endif