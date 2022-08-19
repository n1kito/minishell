#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 10:05:59 by mjallada          #+#    #+#              #
#    Updated: 2022/08/18 10:10:05 by mjallada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME			:= minishell
CC			:= cc
CFLAGS			:= -Wall -Wextra -Werror

INC_DIR			:= include
SRC_DIR			:= src
BIN_DIR			:= bin

LIB_DIR			:= libft
LIB				:= $(shell echo $(LIB_DIR) | cut -c 4-)

# **************************************************************************** #
# COLORS

GREEN			:= \033[0;92m
BGREEN			:= \033[1;92m
RED				:= \033[0;31m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
PURPLE			:= \033[0;35m
IPURPLE			:= \033[3;35m
RED_BLINK		:= \033[31;5m
END_COLOR		:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES		:= 	main\
					tokenizer/tokenizer\
					tokenizer/tokenizer_analysers\
					tokenizer/tokenizer_analysers_2\
					tokenizer/tokenizer_handlers\
					tokenizer/tokenizer_handlers_2\
					tokenizer/tokenizer_utils\
					parser/expander\
					parser/expander_analysers\
					parser/expander_utils\
					parser/parser\
					parser/parser_identify_tokens\
					parser/parser_syntax_checker
OBJ_FILES		:=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# **************************************************************************** #
# RULES

all: header $(NAME)
# I can't include norm check for now because it does not work.
#all: header norm $(NAME)

$(NAME): $(OBJ_FILES)
	@make --no-print-directory -C libft
	@$(CC) -o $(NAME) $(OBJ_FILES) -L $(LIB_DIR) -l $(LIB)
	@echo "\n🔥 $(RED_BLINK)$(NAME) compiled$(END_COLOR) 🔥\n"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	@$(CC) -MD -g -c $(CFLAGS) -I $(INC_DIR) -I $(LIB_DIR)/$(INC_DIR) $< -o $@
	@printf "\r> $(BLUE)compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR) $(BIN_DIR)/tokenizer $(BIN_DIR)/parser
	@echo "$(IPURPLE)Created $(BIN_DIR)/ directory.$(END_COLOR)"

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) all object & dependency files cleaned.$(END_COLOR)"
	@make clean --no-print-directory -C libft

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) executable file cleaned.$(END_COLOR)"
	@rm -f libft/libft.a
	@echo "$(YELLOW)$(LIB_DIR) executable file cleaned as well!$(END_COLOR)"

re: fclean space all
	@#echo "Cleaned all and rebuilt $(NAME) and $(LIB_DIR)! ✔️"

header:
	@echo "😈 $(NAME)\n"

space:
	@echo

norm:
	@echo "😼 Norm check..."
	@norminette src/*/*.c include/*.h | if grep -qc Error: ; then echo "\r🙀 $(RED)Norm errors. 💀$(END_COLOR)     "; else echo "\r😻 Norm $(BGREEN)OK$(END_COLOR)      "; fi
# i need to fix this, norminette does not finish in time for grep and it gives me a Broken pipe error.
	@echo

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re header space norm
