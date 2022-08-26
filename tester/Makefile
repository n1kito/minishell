MAIN_FILES		=	../src/tokenizer/tokenizer.c\
					../src/tokenizer/tokenizer_analysers.c\
					../src/tokenizer/tokenizer_analysers_2.c\
					../src/tokenizer/tokenizer_handlers.c\
					../src/tokenizer/tokenizer_handlers_2.c\
					../src/tokenizer/tokenizer_utils.c\
					../src/parser/parser.c\
					../src/parser/parser_syntax_checker.c\
					../src/parser/expander.c\
					../src/parser/expander_analysers.c\
					../src/parser/expander_utils.c\
					../src/minishell_utils.c
TOKENIZER_MAIN	=	tester_tokenizer.c
PARSER_MAIN		=	tester_parser.c
EXPAND_MAIN		=   tester_quote_expansion.c
INCLUDE_FOLDER	=	include
LIB_DIR			=	libft
LIB				=	ft

YELLOW			:= \033[0;93m
END_COLOR		:= \033[0;39m

all: test

tokenizer:
	@make --no-print-directory -C ../libft
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${TOKENIZER_MAIN} -I ../${INCLUDE_FOLDER} -I ../libft/include -L ../${LIB_DIR} -l ${LIB} -o tokenizer

parser:
	@make --no-print-directory -C ../libft
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${PARSER_MAIN} -I ../${INCLUDE_FOLDER} -I ../libft/include -L ../${LIB_DIR} -l ${LIB} -o parser

expander:
	@make --no-print-directory -C ../libft
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${EXPAND_MAIN} -I ../${INCLUDE_FOLDER} -I ../libft/include -L ../${LIB_DIR} -l ${LIB} -o expander

test:
	@./minishell_tester.sh

clean:
	@rm tokenizer parser expander
	@echo "${YELLOW}Deleted executables.${NC}"

.PHONY: all tokenizer parser test clean
