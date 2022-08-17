MAIN_FILES		=	../tokenizer/tokenizer.c\
					../tokenizer/tokenizer_analysers.c\
					../tokenizer/tokenizer_analysers_2.c\
					../tokenizer/tokenizer_handlers.c\
					../tokenizer/tokenizer_handlers_2.c\
					../tokenizer/tokenizer_utils.c\
					../parser/parser.c\
					../parser/parser_identify_tokens.c\
					../parser/parser_syntax_checker.c\
					../parser/parser_quotes_and_expansions.c
TOKENIZER_MAIN	=	tester_tokenizer.c
PARSER_MAIN		=	tester_parser.c
EXPAND_MAIN		=   tester_quote_expansion.c
INCLUDE_FOLDER	=	../../include

YELLOW			:= \033[0;93m
END_COLOR		:= \033[0;39m

tokenizer:
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${TOKENIZER_MAIN} -I${INCLUDE_FOLDER} -o tokenizer

parser:
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${PARSER_MAIN} -I${INCLUDE_FOLDER} -o parser

expander:
	@gcc -g -Wall -Wextra -Werror ${MAIN_FILES} ${EXPAND_MAIN} -I${INCLUDE_FOLDER} -o expander

test:
	@./minishell_tester.sh

clean:
	@rm tokenizer parser
	@echo "${YELLOW}Deleted executables.${NC}"

.PHONY: all tokenizer parser test clean
