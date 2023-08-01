# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 14:06:30 by marirodr          #+#    #+#              #
#    Updated: 2023/08/01 12:26:48 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

CC			= gcc

#-fsanitize=thread -g

CTHR		= -pthread

CFLAGS	= -g -Wall -Wextra -Werror

SRC			= src/philosophers.c \
						src/print_n_free.c \
						src/check_arg.c \
						src/time.c \
						src/init.c \
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