# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosinga <tosinga@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 13:30:17 by tosinga           #+#    #+#              #
#    Updated: 2022/09/28 16:37:30 by tosinga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo.a

SRC		=	./src/main.c				\
			./src/utils.c				\
			./src/init.c				\
			./src/atoi.c				\
			./src/monitor.c				\
			./src/error_handling.c		\
			./src/philosophers.c		\
			./src/routine.c				\
			./src/routine_actions.c

HEADER	=	./include/philosophers.h
OBJECTS =	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror
CC		=	gcc

all: $(NAME)

$(NAME):$(OBJECTS) $(HEADER)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
		@echo "maked"

%.o: %.CC	
		$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
		@$(RM) $(OBJECTS)
		@echo "maked clean"

fclean: clean
		@$(RM) $(NAME)
		@echo "maked fclean"

re:		fclean all

.PHONY: all clean fclean re