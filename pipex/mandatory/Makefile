# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaez-ga <gpaez-ga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 18:40:23 by gpaez-ga          #+#    #+#              #
#    Updated: 2024/02/05 04:25:07 by gpaez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME = pipex
SRC = main.c commands.c utils.c family.c

OBJ = $(SRC:.c=.o)

LIBFT = ./../libft

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