# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/14 23:36:23 by swied             #+#    #+#              #
#    Updated: 2025/08/05 18:46:30 by swied            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror
INCD := include
SRCD := src
OBJD := obj
LIBFT_DIR := $(INCD)/libft
LIBFT := $(LIBFT_DIR)/libft.a

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

SRCS :=			$(SRCD)/execute.c \
				$(SRCD)/garbage.c \
				$(SRCD)/pwd.c \
				$(SRCD)/echo.c \
				$(SRCD)/cd.c \
				$(SRCD)/execute_utils.c \
				$(SRCD)/env.c \
				$(SRCD)/builtin.c \
				$(SRCD)/get_path.c \
				$(SRCD)/redirect.c \
				$(SRCD)/pipes.c \
				$(SRCD)/main.c \
				$(SRCD)/heredoc.c \
				$(SRCD)/heredoc_utils.c \
				$(SRCD)/exit.c \
				$(SRCD)/env_list.c \
				$(SRCD)/export.c \
				$(SRCD)/list_to_dblarray.c

OBJS := $(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

all: $(NAME)

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJD)/%.o: $(SRCD)/%.c|  $(OBJD)
	@printf "$(YELLOW)Compiling $<...$(NC)\n"
	@$(CC) $(CFLAGS) -I $(INCD) -c $< -o $@
	@printf "$(GREEN)Compiled $< successfully!$(NC)\n"

$(OBJD):
	mkdir -p $(OBJD)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN)Executable $(NAME) built successfully!$(NC)\n"

clean:
	@printf "$(RED)Cleaning object files...$(NC)\n"
	rm -rf $(OBJD)
	@printf "$(GREEN)Object files cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf "$(RED)Cleaning library and executable...$(NC)\n"
	rm -f $(NAME)
	@printf "$(GREEN)Executable cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re