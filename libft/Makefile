# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjallada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 09:49:28 by mjallada          #+#    #+#              #
#    Updated: 2022/06/24 08:56:48 by mjallada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME			:= libft.a
TYPE			:= library

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
AR 				:= ar rc

INC_DIR			:= inc
SRC_DIR			:= src
BIN_DIR			:= bin

# **************************************************************************** #
# COLORS

GREEN			:= \033[0;92m
YELLOW			:= \033[0;93m
BLUE			:= \033[0;94m
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

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $(NAME) $(OBJ_FILES)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BIN_DIR)
	@$(CC) -MD -c $(CFLAGS) -I $(INC_DIR) $< -o $@
	@echo "$(BLUE)Compiling $(notdir $<)$(END_COLOR)"

$(BIN_DIR):
	@mkdir $(BIN_DIR)
	@echo "Created $(BIN_DIR)/ directory."

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(YELLOW)$(NAME) all object & dependency files cleaned.$(END_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)$(NAME) $(TYPE) file cleaned.$(END_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME)!$(END_COLOR)"

-include $(OBJ_FILES:%.o=%.d)

# **************************************************************************** #
# PHONY

.PHONY: all clean fclean re
