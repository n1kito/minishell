# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 10:05:59 by mjallada          #+#    #+#              #
#    Updated: 2022/06/24 09:02:44 by mjallada         ###   ########.fr        #
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
LIB			:= $(shell echo $(LIB_DIR) | cut -c 4-)

# **************************************************************************** #
# COLORS

GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
PURPLE			:= \033[0;35m
IPURPLE			:= \033[3;35m
END_COLOR		:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES		:=
OBJ_FILES		:=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# **************************************************************************** #
# RULES

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make -C libft
	@$(CC) -o $(NAME) $(OBJ_FILES) -L $(LIB_DIR) -l $(LIB)
	@echo "$(GREEN)$(NAME) compiled 🔥$(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile libft/src/*.c | $(BIN_DIR)
	@$(CC) -MD -c $(CFLAGS) -I $(INC_DIR) -I $(LIB_DIR)/$(INC_DIR) $< -o $@
	@echo "$(BLUE)> compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BIN_DIR)
	@$(CC) -MD -c $(CFLAGS) -I $(INC_DIR) $< -o $@
	@echo "$(BLUE)Compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@echo "$(IPURPLE)Created $(BIN_DIR)/ directory.$(END_COLOR)"

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) all object & dependency files cleaned.$(END_COLOR)"
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) executable file cleaned.$(END_COLOR)"
	@rm -f libft/libft.a
	@echo "$(YELLOW)$(LIB_DIR) executable file cleaned as well!$(END_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME) and $(LIB_DIR)!$(END_COLOR)"

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re bonus
