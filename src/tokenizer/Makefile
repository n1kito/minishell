NAME			=	tokenizer
MAIN_FILE		=	tokenizer.c
DEBUG_FILE		=	tokenizer_for_debugging.c
GENERAL_FILES	=	tokenizer_analysers.c\
					tokenizer_analysers_2.c\
					tokenizer_handlers.c\
					tokenizer_handlers_2.c\
					tokenizer_test_utils.c\
					tokenizer_utils.c

YELLOW			:= \033[0;93m
END_COLOR		:= \033[0;39m

all:
	@gcc -Wall -Wextra -Werror ${MAIN_FILE} ${GENERAL_FILES} -I../../include -o ${NAME}

test:
	@./tokenizer_tester.sh

visual:
	@gcc -Wall -Wextra -Werror -D VISUAL ${DEBUG_FILE} ${GENERAL_FILES} -I../../include -o ${NAME}

clean:
	@rm ${NAME}
	@echo "${YELLOW}Deleted ${NAME} executable.${NC}"

.PHONY: all visual test clean
