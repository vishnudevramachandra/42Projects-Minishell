# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC = cc
LDFLAGS = -lreadline -L/usr/local/opt/readline/lib -lft -L./libft
CFLAGS = -Wextra -Wall -Werror -I/usr/local/opt/readline/include -I./libft

NAME = minishell
LIB_NAME = libft.a
LIB = -L ./libft/
CUR_DIR = $(shell pwd)
LIB_PATH = $(CUR_DIR)/libft/

all: $(NAME)

$(NAME): $(LIB_PATH)/$(LIB_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) shell.c -o $(NAME)
	@echo "$(GREEN)$(NAME) executable created successfully!$(RESET)\n"

$(LIB_PATH)/$(LIB_NAME):
	make -C $(LIB_PATH)

.PHONY: clean fclean re

clean:
	make clean -C $(LIB_PATH)
	
fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed successfully!$(RESET)\n"

re: fclean all