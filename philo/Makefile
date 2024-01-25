# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleperei <aleperei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 14:05:13 by aleperei          #+#    #+#              #
#    Updated: 2024/01/25 18:03:10 by aleperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -pthread

RM = rm -f

SRCS = philo.c utils.c \

OJBS = $(SRCS:.c=.o)



$(NAME):	$(OJBS)
	$(CC) $(CFLAGS) $(OJBS) -o $(NAME)

all: $(NAME)

#clean mandatory ojbs
clean:
	@$(RM) $(OJBS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re