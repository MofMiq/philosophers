# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 14:06:30 by marirodr          #+#    #+#              #
#    Updated: 2023/08/09 18:33:33 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= gcc


CTHR		= -pthread
# -fsanitize=thread -g
CFLAGS	= -Wall -Wextra -Werror

SRC			= src/philo.c \
						src/print_n_free.c \
						src/check_arg.c \
						src/time.c \
						src/loop.c \
						src/rutine.c \

OBJ			= $(SRC:.c=.o)

GREEN		= \033[0;32m
RED			= \033[0;31m
END			= \033[0m

RM			= rm -rf

all:	$(NAME)

$(NAME): $(OBJ)
								$(CC) $(CTHR) $(CFLAGS) $(OBJ) -o $(NAME)
								@echo "$(GREEN) Philosophers ready$(END)"
								@echo "$(GREEN) Format: [number of philosophers] [time to die] [time to eat] [time to sleep] {number of times}$(END)"

.c.o:						$(CC) $(CTHR) $(CFLAGS) -c $< -o $@

clean:
								$(RM) $(OBJ)
								@echo "$(RED)Compiled objects have been removed$(END)"

fclean: clean
								$(RM) $(NAME)
								@echo "$(RED)Executables objects have been removed$(END)"

re: fclean all

.PHONY: all, clean, fclean, re