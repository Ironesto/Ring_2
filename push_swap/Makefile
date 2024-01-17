# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 19:56:02 by gpaez-ga          #+#    #+#              #
#    Updated: 2023/12/06 04:48:01 by gpaez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME = push_swap
SRC = valid.c moves.c tools.c basic.c advance.c main.c

OBJ = $(SRC:.c=.o)

LIBFT = libft

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(OBJ) $(LIBFT)/libft.a -o $(NAME)
	

clean:
	make -C $(LIBFT) clean
	$(RM) $(OBJ) 

fclean:
	make -C $(LIBFT) fclean
	$(RM) $(OBJ) $(NAME)

re: fclean all