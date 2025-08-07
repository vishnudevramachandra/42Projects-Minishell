# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:03:12 by vramacha          #+#    #+#              #
#    Updated: 2025/05/15 14:13:47 by vramacha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
RESET       = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_toupper.c ft_tolower.c \
	ft_isascii.c ft_isprint.c ft_strlen.c ft_strchr.c ft_strncmp.c ft_memset.c \
	ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_strlcpy.c \
	ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strrchr.c
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME).a

$(NAME).a: $(OBJS) $(BONUS_OBJS)
	ar -rcs $@ $^
	@echo "$(GREEN)$(NAME) archive created successfully!$(RESET)\n"


.PHONY: clean fclean re
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	@echo "$(RED)$(NAME) objects cleaned successfully!$(RESET)\n"

fclean: clean
	rm -f $(NAME).a
	@echo "$(RED)$(NAME) archive cleaned successfully!$(RESET)\n"

re: fclean all
