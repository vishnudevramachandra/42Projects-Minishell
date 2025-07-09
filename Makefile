# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC = cc
LDFLAGS = -lreadline
CFLAGS = -Wextra -Wall -Werror

NAME = minishell

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(LDFLAGS) shell.c -o $(NAME)
	@echo "$(GREEN)$(NAME) executable created successfully!$(RESET)\n"

.PHONY: clean fclean re

clean:

fclean:

re:
