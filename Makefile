# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 10:05:59 by mjallada          #+#    #+#              #
#    Updated: 2022/08/26 03:02:11 by vrigaudy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME			:= minishell
CC			:= cc
CFLAGS			:= -Wall -Wextra -Werror -g

INC_DIR			:= include
SRC_DIR			:= src/*/
BIN_DIR			:= bin

LIB_DIR			:= libft
LIB			:= $(shell echo $(LIB_DIR) | cut -c 4-)

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

SRC_FILES		:= 	main.c \
					get_env.c \
					env_for_exe.c \
					export.c \
					unset.c \
					env.c

OBJ_FILES		:=	$(SRC_FILES:%.c=$(BIN_DIR)/%.o)

# **************************************************************************** #
# RULES

all: header norm $(NAME)

$(NAME): $(OBJ_FILES)
	make --no-print-directory -C libft
	$(CC) -o $(NAME) $(OBJ_FILES) -L $(LIB_DIR) -l $(LIB) -lreadline
	echo "\n🔥 $(RED_BLINK)$(NAME) compiled$(END_COLOR) 🔥\n"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	$(CC) -MD -c $(CFLAGS) -I $(INC_DIR) -I $(LIB_DIR)/inc/ $< -o $@
	printf "\r> $(BLUE)compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
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
	@echo -n "😼 Norm check..."
	@norminette | if grep -qc Error: ; then echo "\r🙀 $(RED)Norm errors. 💀$(END_COLOR)     "; else echo "\r😻 Norm $(BGREEN)OK$(END_COLOR)      "; fi
	@echo

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re header space norm
