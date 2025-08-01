# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC = cc
LDFLAGS = -lreadline -L/usr/local/opt/readline/lib
CFLAGS = -Wextra -Wall -Werror -I/usr/local/opt/readline/include

NAME = minishell

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(LDFLAGS) shell.c -o $(NAME)
	@echo "$(GREEN)$(NAME) executable created successfully!$(RESET)\n"

.PHONY: clean fclean re

clean:

fclean: clean
	rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed successfully!$(RESET)\n"

re: fclean all