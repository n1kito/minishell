# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 09:49:28 by mjallada          #+#    #+#              #
#    Updated: 2022/08/31 06:30:09 by mjallada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME			:= libft.a
TYPE			:= library

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
AR 				:= ar rc

INC_DIR			:= include
SRC_DIR			:= src
BIN_DIR			:= bin

# **************************************************************************** #
# COLORS

GREEN			:= \033[0;92m
RED				:= \033[0;31m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
PURPLE			:= \033[0;35m
IPURPLE			:= \033[3;35m
END_COLOR		:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC_FILES		:=	ft_isalpha \
					ft_isdigit \
					ft_isalnum \
					ft_isascii \
					ft_isprint \
					ft_strlen \
					ft_memset \
					ft_bzero \
					ft_memcpy \
					ft_memmove \
					ft_strlcpy \
					ft_strlcat \
					ft_toupper \
					ft_tolower \
					ft_strchr \
					ft_strrchr \
					ft_strncmp \
					ft_strcmp \
					ft_memchr \
					ft_memcmp \
					ft_strnstr \
					ft_atoi \
					ft_calloc \
					ft_strdup \
					ft_substr \
					ft_strjoin \
					ft_strtrim \
					ft_split \
					ft_itoa \
					ft_strmapi \
					ft_striteri \
					ft_putchar_fd \
					ft_putstr_fd \
					ft_putendl_fd \
					ft_putnbr_fd \
					ft_lstnew \
					ft_lstadd_front \
					ft_lstsize \
					ft_lstlast \
					ft_lstadd_back \
					ft_lstdelone \
					ft_lstclear \
					ft_lstiter \
					ft_lstmap \
					ft_printf_fd \
					get_next_line \
					get_next_line_utils
OBJ_FILES		:=	$(addprefix $(BIN_DIR)/, $(addsuffix .o, $(SRC_FILES)))

# **************************************************************************** #
# RULES

#all: space header $(NAME)
all: space $(NAME)

$(NAME): $(OBJ_FILES)
	@@echo "\n++ building $(NAME)"
	@$(AR) $(NAME) $(OBJ_FILES)
	@echo "\n++ $(GREEN)$(NAME) compiled :)$(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BIN_DIR)
	@$(CC) -MD -c $(CFLAGS) -I $(INC_DIR) $< -o $@
	@printf "\r++ $(BLUE)compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@echo "++ $(IPURPLE)created $(BIN_DIR)/ directory.$(END_COLOR)"

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) all object & dependency files cleaned.$(END_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) $(TYPE) file cleaned.$(END_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME)!$(END_COLOR)"

header:
	@echo "\n++ building $(NAME)"

space:
	@echo

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re header space
