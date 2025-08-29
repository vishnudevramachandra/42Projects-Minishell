# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/27 21:32:53 by vishnudevra       #+#    #+#              #
#    Updated: 2025/08/29 14:11:03 by vishnudevra      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC 		= cc
LDFLAGS = -lreadline -lft -L./libft #-L/usr/local/Cellar/readline/8.3/lib
CFLAGS	= -Wextra -Wall -Werror -I./libft #-I/usr/local/Cellar/readline/8.3/include

NAME		= minishell
LIB_NAME 	= libft.a
LIB 		= -L ./libft/
CUR_DIR 	= $(shell pwd)
LIB_PATH	= $(CUR_DIR)/libft/

SRC =	shell.c \
		lexer.c lexer_inits.c lexer_basicfcns.c lexer_helper.c lexer_exp.c \
		lexer_metachar.c \
		parser.c parser_helper.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB_PATH)/$(LIB_NAME) $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) executable created successfully!$(RESET)\n"

$(LIB_PATH)/$(LIB_NAME):
	make -C $(LIB_PATH)

.PHONY: clean fclean re

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJ)
	
fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed successfully!$(RESET)\n"

re: fclean all